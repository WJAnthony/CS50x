# KNOWYOURMEAT.COM
## Introduction
This is the README file that explains my final project for the Havard CS50x course on edx. The purpose of this file is to document my project thoroughly as well as all aspects of its functionality. This later part of this section describes what my project is, and the later sections will explain each of the files I have wrote/coded for this project.

### Details
Some details:
- Project title: KnowYourMeat.com
- Name: Anthony Chow
- Github username: WJAnthony
- EDx username: Anthony_2471
- Country & City: Singapore, Singapore
- Video Demo: <URL https://youtu.be/UCrFuH6c4MQ>

### Inspiration
The inspiration for this project comes from a personal hobby of mine: the Gym.

Due to the numerous health benefits that going to the gym regularly brings, me and my friends have began our fitness journey at the start of the the year. I visit the gym regularly, arround 4 to 5 times a weeks for 2 hours, with a focus on lifting weights.
My goal going to the gym is to increase my lean muscle mass AKA building more muscles.

However, muscle mass is not just build in the gym but also in the kitchen. According to the American College of Sports Medicine: "to increase muscle mass in combination with physical activity, it is recommended that a person that lifts weights regularly should eat a range of 1.2-1.7 grams of protein per kilogram of body weight per day".

Therefore, in order to maximise gains in the gym, i have to ensure i consume a sufficient amount of protein in a day. However, not all protein sources are created equally. Like most people, most of the protein in my diet comes from animal sources (e.g. Chicken), but different meats each have a unique nutriental content. Each meat option has a different amount of protein, fats, calories (assuming a fixed mass of meat). Therefore, I decided to focus my final project on educating visitors on the different nutritional quantities in meats, explaining what protien is, presenting information on the 30 most common meats source and allwoing visitors to compare them. The purpose is to not only eudcate users but also provide them a tool to compare meat source they are considering, allowing them to make a better dietary decision for their own unique health goals.

### Description
My final project, KnowYourMeat.com, is a web-based application using JavaScript, Python, and SQL and it is coded in VS. It is an educational web-based application, with a focus on educating users on various nutriental topics within the subject of meats as well as an interactive platform to compare between different meat options avaiable.

The website, client side, was built using HTML as its base with CSS used for the websites aesthetics and JavaScript to allow the website's interactive features to function. Python was used as the server side programming language, to code the backbone function of the web-based application. SQL was used to store data, in the form of SQL databases with tables of data/information on the nutriental content of the 30 most common meat options.

There is a total of 7 separate HTML files used in this web-based application, all of which are stored in the templates folder. The following section will describe and explain 1 HTML file per sub-section. The python code, which is in the app.py file, will be explained in the following section titled app.py. The use of SQL will be explained in SQL database section. Lastly, the CSS file as well as other files stored in the static folder will be explained in the static section of this README.

## Templates (html)
There is a total of 7 seperate HTML files used in this web-based application. They are titled: layout, Index, Nutrients, Protein, Tabulated as well as Compare and Compared .html. Each HTML file will be explained below.

### Layout
This is the based html page upon which the rest of the HTMLs are extended on.

At the top of the file, bootstrap and flavicons are added. The top of the page is the header and the navigation bar to allow users to navigate the different pages of this web-based application. The middle part of the page is the body in which the other pages' content is displayed. At the bottom of the page is the footer.

### Index
This is the Homepage of this web-based application. It is the first page a user will see upon clicking the link of this web-based application. It can also be access from any part of the website by clicking the "homepage" in the Navigation bar.

The homepage has 3 sections of text. The first section is an introduction to the website, the second is an introduction to the subject this website is based on, the third is why this website and its content is beneficial to users and the last is a disclaimer. Each section also preludes users to a different part of the website.

### Nutrients
This page explains the 6 nutrients that this website will compare: Calories, Protein, Fats, Saturated fats, Monounsaturated fats and Polyunsaturated fat. Users can navigate to this page by clicking on "nutrients" in the navbar.

The nutrients page has 2 sections. The first section is an introduction to the page and the second section is a list of cards. The second section is an implementation of a bootstrap component: cards. Additional features were added into each card, such as buttons. Each card explains one of the 5 nutrients as listed above and if the user is interested in learning more, they can click the learn more button of each card to learn more about the respective nutrient as the buttons will direct them to another website.

### Protein
This page explains the 5W1H of protein, from what is protein, the uses of protein as well as the building blocks of proteins: Amino Acids. User can navigate to this page by clicking on "protein" in the navbar.

The protein page has 2 sections. The first section is an introduction to the page and the second section is an implementation of a bootstrap component: vertically collapsable accordion. The second section's content is on the different types of amino acids. Therefore I decided to use accordion to prevent the page being too wordy, allowing users to click on the accordion tabs to reveal more information.

### Tabulated
This page displays all the 30 meat options in a table which includes information on the meats' calories, proteins, fats, saturated fats, monounsaturated fats and polyunsaturated fats in kcal or grams per 100g of meat. Users can navigate to this page by clicking on "tabulated data" in the navbar.

The tabulated page has 2 sections. The first section is an introduction to the page and explains how to use the table.

The second section is a table containing all 30 meat options and their nutriental quantities. When building the table, I avoided hardcoding all the data into the table, instead opting to use a jinja loop to insert into each row a meat option and its nutrient quantities reading from a SQL database table, thus each meat option had its own row. I chose to do so because I wanted to populate the table more efficiently and to make the table more dynamic. In the future if the SQL database table expands or shrink, the table's size will adjust automatically.

The table is also a sortable table. By clicking on the headers of the table, users will be able to sort the table based on the numeric value of the nutriental quantity of the respective header. Click once for ascending and another for descending. The sortable function of the table was coded using Javascript located in the script part of the html file. It uses a sorting function to do the sorting when the respective header is clicked. I chose to make the table sortable as it makes the table more user friendly and a better way for users to view the data in a way that is more useful for users. This table also makes this page more interative for users.

### Compare
This page is part one of two of the compare feature of this website. The purpose of the compare feature is to allow users to select 5 different meat options via a form and view the comparison between them through a focused table and data visualisation.

The compare html file displays a form with each of the 30 meat options as a checkbox input together with a submit button to submit the form. Users can navigate to this page by clicking on "compare" in the navbar.

The purpose of the form is to allow users to select 5 meat options to compare. This is beacuse it is unlikely users have access to all 30 meat options in this web-based application and likely only consume a select few. Users will also want to focus on just a few meat options and compare them, which is challenging when using the tabulated data table.

Similar to the table in tabulated data, I avoided hardcoding all the checkboxes, opting to use a jinja loop to populate the form with each of the 30 meat options as checkboxes input, reading from a SQL database table, in the form. The reasons are similar too, one is efficiency and the other to make the form more dynamic.

Javascript is also utilised in this page, found in the script part of the html form. Javascript was used to limit the number of checkboxes that the user can check. If the user attempts to click the 6th checkbox, the Javascript will stop the action and alert the user to check only 5 checkboxes.

### Compared
This page is part two of two of the compare feature of this website and it will appear after the submit button in the compare page is clicked.

This page contains 2 sections, the first is the graphs section and the second is a sortable table.

After the form is submitted, the nutrientional information of the 5 meat options selected will be displayed in this "compared" page. In the first section is 3 bar graphs, comparing the Calories, Protein and Fats of the 5 meat options. This data visualisation allows the web-based application to be more interative and user-friendly as it provides a different way to view the data, not just using numbers. The graphs were coded using Javascipt.

The second section is a small sortable table with only the data from the 5 meat options selected displayed below as a summary tool. The table is similar to the one in tabulated data, using a jinja loop to populate it as well.

## App.py
This is the file containing the Python code for this web-based application. Python is used as the server-side language to tie in the SQL database with the rest of html files and the allow the website to function as intended.

At the top of the file, I imported several features such as redirect and render_template from flask and SQL from cs50. I also configure CS50 Library to use SQLite database.

The main body of the file is the python code for each of the html files such as rendering templates when a certain tab is clicked. For tabulated data html, python is used to read the data from SQL and gives it to the file for the table to be populated using jinja syntax. For compare html, both POST and GET are included as methods. This is so that if user reached route via GET (as by clicking a link or via redirect), they will see the checkbox form. After clicking submit, the code will read the relevant data from the SQL database and allow for the compare table and graphs to be populated.

## Static
Two static files are present.

### Flavicon icons
Two flavicon icons were used. One is the slice of meat found in the header as well as in the brower tab and the other is a house used to represent the homepage in the navigation bar.

### Styles.CSS
The styles.css file is a CSS file for the aesthetics of this web-based application

## SQL database
One database was used.

### Meats database
The Meats databse contains 2 tables. One is the "meats", a two column table containing the name of all the 30 meat options. The other table, "meats_for_comparison" is a larger table containing all 30 meat options as well as the amount of protein, calories, fats, MUF, PUF and SF of each meat option, all in the form of a float.
