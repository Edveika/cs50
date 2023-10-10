import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

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

    if request.method == "GET":
        purchase_data = db.execute("SELECT * FROM purchases WHERE user_id=?", session["user_id"])
        cur_user_data = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])
        user_cash = float(cur_user_data[0]["cash"])

        stock_sum = 0
        for data in purchase_data:
            stock_sum += data["amount"] * lookup(data["stock"])["price"]
        
        total = user_cash + stock_sum

        return render_template("index.html", purchase_data=purchase_data, lookup=lookup, round=round, total=total, user_cash=user_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        cur_user_data = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])
        user_cash = float(cur_user_data[0]["cash"])

        stock_symbol = request.form.get("stock-symbol")
        stock_data = lookup(stock_symbol)
        stock_price = float(stock_data["price"])
        if len(stock_symbol) == 0 or stock_data == None:
            return apology("Stock symbol field cannot be empty and must be valid")

        stock_count = int(request.form.get("share-amount"))
        if stock_count < 0:
            return apology("Share number must be a positive number")

        if stock_price * stock_count > user_cash:
            return apology("Sorry, cant afford")

        user_has_stock = db.execute("SELECT stock FROM purchases WHERE user_id=? AND stock=?", session["user_id"], stock_symbol)
        if len(user_has_stock) == 0:
            db.execute("INSERT INTO purchases (amount, stock, user_id) VALUES(?, ?, ?)", stock_count, stock_symbol, session["user_id"])
        else:
            db.execute("UPDATE purchases SET amount=amount+? WHERE user_id=? AND stock=?", stock_count,session["user_id"], stock_symbol)
        
        db.execute("INSERT INTO purchase_history (symbol, count, purchase_date, old_price, user_id) VALUES(?, ?, ?, ?, ?)", stock_symbol, stock_count, datetime.datetime.now(), stock_price, session["user_id"])

        db.execute("UPDATE users SET cash=? WHERE id=?", user_cash - (stock_price * stock_count), session["user_id"])

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        stock_symbol = request.form.get("stock-symbol")
        if len(stock_symbol) == 0:
            return apology("Stock symbol cannot be empty")
        
        print(stock_symbol)
        lookup_data = lookup(stock_symbol)

        return render_template("quoted.html", lookup_data=lookup_data)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        name = request.form.get("username")
        if len(name) == 0:
            return apology("Unique username required")

        password = request.form.get("password")
        confirm_password = request.form.get("confirm-password")
        if len(password) == 0 or len(confirm_password) == 0 or password != confirm_password:
            return apology("Password must not be empty and both fields have to match")

        hashed_password = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, hashed_password)

        return redirect("login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
