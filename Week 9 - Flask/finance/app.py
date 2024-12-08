import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Select stocks and quantity from portfolio
    stocks = db.execute("SELECT stock, quantity FROM portfolio WHERE user_id = ? GROUP BY stock", session["user_id"])

    for stock in stocks:
        stock["symbol"] = stock["stock"]
        stock["quantity"] = stock["quantity"]

        quote = lookup(stock["symbol"])
        stock["current_price"] = quote["price"]
        stock["total_value"] = (quote["price"] * stock["quantity"])

    # Query database for funds
    user_id = session["user_id"]
    cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", user_id
    )
    funds = float(cash[0]["cash"])

    # Grand total
    total = 0
    for stock in stocks:
        total = total + stock["total_value"]
    grand_total = total + funds

    return render_template("index.html", stocks=stocks, funds=usd(funds), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock's symbol", 400)

        # Ensure stock symbol submitted exist
        quoted = lookup(request.form.get("symbol"))
        if not quoted:
            return apology("stock's symbol does not exist", 400)

        # Ensure number of shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares to buy", 400)

        # Ensure number of shares submitted is not a fraction, negative or non-digit
        elif not request.form.get("shares").isdigit():
            return apology("input a positive integer", 400)

        # lookup stock's price
        price = float((quoted["price"]))

        # Buy the stock (price x no. of shares) & deduct from cash in user
        cost = float(price * int(request.form.get("shares")))

        # Query database for funds
        user_id = session["user_id"]
        cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id
        )
        funds = float(cash[0]["cash"])

        # If user has insufficent funds
        if (funds < cost):
            return apology("Insufficent funds", 400)
        else:
            now = datetime.now()
            # Update portfolio table
            existing = db.execute("SELECT * FROM portfolio WHERE stock = ? AND user_id = ?", request.form.get("symbol"), user_id)
            if not existing:
                db.execute("INSERT INTO portfolio (user_id, stock, quantity) VALUES(?, ?, ?)",
                           user_id, request.form.get("symbol"), int(request.form.get("shares")))
            else:
                db.execute("UPDATE portfolio SET quantity = ? WHERE user_id = ? AND stock = ?",
                           (existing[0]["quantity"] + int(request.form.get("shares"))), user_id, request.form.get("symbol"))

            # Input into transactions table
            db.execute("INSERT INTO transactions (user_id, stock, price, quantity, date, type) VALUES(?, ?, ?, ?, ?, ?)",
                       user_id, request.form.get("symbol"), price, int(request.form.get("shares")), now, "Purchase")

            # Update user table
            remaining_funds = funds - cost
            db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_funds, user_id)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure symbol input is not blank
        if not request.form.get("symbol"):
            return apology("must provide stock's symbol", 400)

        # Ensure stock symbol submitted exist
        quoted = lookup(request.form.get("symbol"))
        if not quoted:
            return apology("stock's symbol does not exist", 400)

        # Find stocks's price
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        price = usd(float(stock["price"]))

        # Redirect user to quoted.html
        return render_template("quoted.html", symbol=symbol, price=price)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Ensure both passwords match
        elif (request.form.get("password") != request.form.get("confirmation")):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username is not in use
        if len(rows) != 0:
            return apology("Username already in use", 400)

        # Hash password and collect new username
        password = generate_password_hash(request.form.get("password"), method='pbkdf2', salt_length=16)
        username = request.form.get("username")

        # Insert username and password into users in finance.db
        db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username, password)

        # Redirect user to Login page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    user_id = session["user_id"]
    if request.method == "POST":
        # Ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock's symbol", 400)

        # Ensure stock symbol submitted exist
        quoted = lookup(request.form.get("symbol"))
        if (quoted == "None"):
            return apology("stock's symbol does not exist", 400)

        # Ensure number of shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares to buy", 400)

        # Ensure number of shares submitted is not a fraction, negative or non-digit
        elif not request.form.get("shares").isdigit():
            return apology("input a positive integer", 400)

        # lookup stock's price
        price = float((quoted["price"]))

        # Ensure user owns said stock and ensure user owns more or equal to the number of stock to sell
        check_stock = db.execute("SELECT * FROM portfolio WHERE stock = ? AND user_id = ?", request.form.get("symbol"), user_id)
        if not check_stock:
            return apology("You do not own this stock", 400)
        if (check_stock[0]["quantity"] < int(request.form.get("shares"))):
            return apology("You do not own that many shares of this stock", 400)

        # Sell the stock (price x no. of shares) & add cash into user
        value = float(price * int(request.form.get("shares")))

        # Query database for funds
        cash = db.execute(
            "SELECT * FROM users WHERE id = ?", user_id
        )
        funds = float(cash[0]["cash"])

        # Update portfolio table
        now = datetime.now()
        existing = db.execute("SELECT * FROM portfolio WHERE stock = ? AND user_id = ?", request.form.get("symbol"), user_id)
        if (existing[0]["quantity"] > int(request.form.get("shares"))):
            db.execute("UPDATE portfolio SET quantity = ? WHERE user_id = ? AND stock = ?",
                       (existing[0]["quantity"] - int(request.form.get("shares"))), user_id, request.form.get("symbol"))
        elif (existing[0]["quantity"] == int(request.form.get("shares"))):
            db.execute("DELETE FROM portfolio WHERE user_id = ? AND stock = ?",
                       (user_id, request.form.get("symbol")))

        # Input into transactions table
        db.execute("INSERT INTO transactions (user_id,stock, price, quantity, date, type) VALUES(?, ?, ?, ?, ?, ?)",
                   user_id, request.form.get("symbol"), price, int(request.form.get("shares")), now, "Sale")

        # Update user table
        remaining_funds = funds + value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_funds, user_id)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Populate select menu
        rows = db.execute("SELECT * FROM portfolio WHERE user_id = ?", user_id)
        return render_template("sell.html", stocks=rows)


@app.route("/addfunds", methods=["GET", "POST"])
@login_required
def addfunds():
    """Allow users to add additional cash to their account"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure addfunds was submitted
        if not request.form.get("addfunds"):
            return apology("must provide a number", 403)

        # Ensure addfunds is more than $1
        elif (float(request.form.get("addfunds")) < 1):
            return apology("minimun top-up value is 1", 403)

        # Ensure number of shares submitted is not a fraction, negative or non-digit
        elif not request.form.get("addfunds").isdigit():
            return apology("input a positive integer", 400)

        # Query database for funds
        user_id = session["user_id"]
        cash = db.execute(
            "SELECT * FROM users WHERE id = ?", user_id
        )
        funds = float(cash[0]["cash"])

        # Update user table
        new_amount = funds + (float(request.form.get("addfunds")))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_amount, user_id)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("addfunds.html")
