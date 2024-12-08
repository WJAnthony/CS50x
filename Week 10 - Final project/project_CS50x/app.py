import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request
from datetime import datetime
import json

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///meats.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    """Display homepage"""
    return render_template("index.html")


@app.route("/protein")
def protein():
    """Display info about proteins and amino acids"""
    return render_template("protein.html")


@app.route("/nutrients")
def nutrients():
    """Display info about the 5 nutrients compared"""
    return render_template("nutrients.html")


@app.route("/tabulated", methods=["GET", "POST"])
def tabulated():
    """Display table"""
    rows = db.execute("SELECT * FROM meats_for_comparison")
    return render_template("tabulated.html", meats=rows)


@app.route("/compare", methods=["GET", "POST"])
def compare():
    """Compare up to 5 different meats"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        meats_to_compare = request.form.getlist("meats")
        if (len(meats_to_compare) < 5):
            return redirect("/compare")

        rows = db.execute("SELECT * FROM meats_for_comparison WHERE name in (?)", meats_to_compare)

        country = ["Italy", "France", "Spain", "USA", "Argentina"]

        chart_data_calories = {
            "labels": [meats_to_compare[0], meats_to_compare[1], meats_to_compare[2], meats_to_compare[3], meats_to_compare[4]],
            "values": [rows[0]["calories"], rows[1]["calories"], rows[2]["calories"], rows[3]["calories"], rows[4]["calories"]]
        }

        chart_data_protein = {
            "labels": [meats_to_compare[0], meats_to_compare[1], meats_to_compare[2], meats_to_compare[3], meats_to_compare[4]],
            "values": [rows[0]["protein"], rows[1]["protein"], rows[2]["protein"], rows[3]["protein"], rows[4]["protein"]]
        }

        chart_data_fats = {
            "labels": [meats_to_compare[0], meats_to_compare[1], meats_to_compare[2], meats_to_compare[3], meats_to_compare[4]],
            "values": [rows[0]["fats"], rows[1]["fats"], rows[2]["fats"], rows[3]["fats"], rows[4]["fats"]]
        }

        return render_template("compared.html", meats=rows, country=country, chart_data_calories=chart_data_calories, chart_data_protein=chart_data_protein, chart_data_fats=chart_data_fats)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Populate checkboxes menu
        rows = db.execute("SELECT * FROM meats_for_comparison")
        return render_template("compare.html", meats=rows)
