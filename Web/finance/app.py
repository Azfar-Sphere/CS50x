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
    userId = session.get("user_id")
    userStocks = db.execute(
        "SELECT users.id, users.cash, stocks.symbol, stocks.amount FROM users JOIN stocks ON users.id = stocks.id WHERE users.id = ?",
        userId,
    )
    price = {}
    value = {}
    total = 0
    if userStocks:
        for userStock in userStocks:
            symbol = userStock["symbol"]
            amount = int(userStock["amount"])

            stock = lookup(symbol)
            stockPrice = float(stock["price"])

            price[symbol] = usd(stockPrice)
            value[symbol] = usd(stockPrice * amount)
            total += stockPrice * amount

        cash = usd(userStocks[0]["cash"])

        total += float(userStocks[0]["cash"])
        total = usd(total)

        return render_template(
            "index.html",
            userstocks=userStocks,
            price=price,
            value=value,
            cash=cash,
            total=total,
        )

    return render_template("indexalt.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        if not stock:
            return apology("Incorrect Symbol")

        try:
            amount = int(request.form.get("shares"))
            if amount <= 0:
                return apology("Incorrect Number of Stocks")
        except ValueError:
            return apology("Incorrect Number of Stocks")

        totalPrice = float(stock["price"]) * amount
        userId = session.get("user_id")
        cash = db.execute("SELECT cash FROM users WHERE id = ?", userId)
        money = float(cash[0]["cash"])
        if totalPrice > money:
            return apology("Not enough Money")

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", (money - totalPrice), userId
        )
        db.execute(
            "INSERT INTO history (id, symbol, amount, type, time) VALUES (?, ?, ?, ?, ?)",
            userId,
            symbol.upper(),
            amount,
            "Buy",
            datetime.now(),
        )

        userStocks = db.execute(
            "SELECT * FROM stocks WHERE id = ? AND symbol = ?", userId, symbol.upper()
        )
        if not userStocks:
            db.execute(
                "INSERT INTO stocks (id, symbol, amount) VALUES (?, ?, ?)",
                userId,
                symbol.upper(),
                amount,
            )
        else:
            stocksOwned = int(userStocks[0]["amount"]) + amount
            db.execute(
                "UPDATE stocks SET amount = ? WHERE id = ? AND symbol = ?",
                stocksOwned,
                userId,
                symbol.upper(),
            )

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userId = session.get("user_id")
    historys = db.execute("SELECT * FROM history WHERE id = ?", userId)
    price = {}
    for history in historys:
        stock = lookup(history["symbol"])
        stockp = usd(stock["price"])
        price[history["symbol"]] = stockp
    return render_template("history.html", historys=historys, price=price)


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
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        if not stock:
            return apology("Incorrect Stock Symbol")

        price = usd(stock["price"])

        return render_template("quoted.html", symbol=symbol, price=price)

    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        if not username:
            return apology("Please Enter Username")

        if not password:
            return apology("Please Enter Password")

        if not request.form.get("confirmation"):
            return apology("Please Confirm Password")

        if password != request.form.get("confirmation"):
            return apology("Passwords do not match")

        user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if user:
            return apology("Username is taken")

        hashpass = generate_password_hash(password)
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)", username, hashpass
        )
        return redirect("/login")

    return apology("Error")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    userId = session.get("user_id")
    if request.method == "GET":
        userStocks = db.execute("SELECT symbol FROM stocks WHERE id = ?", userId)
        return render_template("sell.html", userStocks=userStocks)

    if request.method == "POST":
        symbol = request.form.get("symbol")
        amount = int(request.form.get("shares"))

        stock = lookup(symbol)
        price = float(stock["price"])
        totalPrice = amount * price

        userStocks = db.execute(
            "SELECT * FROM stocks WHERE id = ? AND symbol = ?", userId, symbol.upper()
        )
        if not userStocks or userStocks[0]["amount"] == 0:
            return apology("You do not Own This Stock")
        if int(userStocks[0]["amount"]) < amount:
            return apology("Incorrect Amount")
        else:
            db.execute(
                "INSERT INTO history (id, symbol, amount, type, time) VALUES (?, ?, ?, ?, ?)",
                userId,
                symbol.upper(),
                amount,
                "Sell",
                datetime.now(),
            )

            stocksOwned = int(userStocks[0]["amount"]) - int(amount)
            if stocksOwned == 0:
                db.execute(
                    "DELETE FROM stocks WHERE symbol = ?",
                    symbol.upper(),
                )
            else:
                db.execute(
                    "UPDATE stocks SET amount = ? WHERE id = ? AND symbol = ?",
                    stocksOwned,
                    userId,
                    symbol.upper(),
                )

            cash = db.execute("SELECT cash FROM users WHERE id = ?", userId)
            money = float(cash[0]["cash"])
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?", (money + totalPrice), userId
            )

    return redirect("/")
