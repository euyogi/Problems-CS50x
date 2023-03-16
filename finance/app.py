import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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

    stocks = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = ?;", session["user_id"])
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]["cash"]

    stocks_total_price = 0
    for stock in stocks:
        stocks_total_price += lookup(stock["symbol"])["price"] * stock["shares"]

    return render_template("index.html", user_cash=user_cash, lookup=lookup, stocks=stocks, stocks_total_price=stocks_total_price)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Search for the stock
        stock = lookup(symbol)

        # Ensure there is a stock with that symbol
        if not stock:
            return apology("invalid symbol", 400)

        # Ensure shares was submitted
        elif not shares:
            return apology("missing shares", 400)

        # Ensure shares is a positive number
        elif not shares.isdigit() or int(shares) < 1:
            return apology("invalid shares", 400)

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]["cash"]
        shares_total_price = stock["price"] * int(shares)

        # Ensure user has enough money to buy shares
        if not user_cash > shares_total_price:
            return apology("can't afford")

        # Insert the new purchase into transactions, along with the stock symbol and price
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, type) VALUES (?, ?, ?, ?, 'purchase');",
                   session["user_id"], stock["symbol"], stock["price"], shares)

        # Insert the stocks bought into stocks, along with the stock symbol
        db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES (?, ?, ?);", session["user_id"], stock["symbol"], shares)

        # Subtract user cash used into that purchase
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", user_cash - shares_total_price, session["user_id"])

        # Success message
        flash('Bought!')

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT symbol, shares, price, type, date FROM transactions WHERE user_id = ?;", session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Success message
        flash('Welcome!')

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


@app.route("/profile", methods=["GET", "POST"])
@login_required
def profile():
    """Show user his username and allow to change username or password"""

    # Gets username
    username = db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])[0]["username"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        new_username = request.form.get("new-username")

        new_password = request.form.get("new-password")
        confirmation = request.form.get("confirmation")

        current_password = request.form.get("current-password")

        current_password_hash = db.execute("SELECT hash FROM users WHERE id = ?;", session["user_id"])[0]["hash"]

        # Ensure passwords are the same
        if not check_password_hash(current_password_hash, current_password):
            return apology("passwords are not the same", 403)

        elif new_username:

            # Ensure username is unique
            if len(db.execute("SELECT username FROM users WHERE username = ?;", new_username)):
                return apology("username already in use", 403)

            # Update username
            db.execute("UPDATE users SET username = ? WHERE id = ?;", new_username, session["user_id"])

        if new_password:

            # Ensure password has atleast 8 characters
            if not len(new_password) >= 8:
                return apology("password need atleast 8 characters", 403)

            # Ensure passwords are the same
            elif not new_password == confirmation:
                return apology("passwords must be the same", 403)

            # Ensure new password is not the same as current password
            elif check_password_hash(current_password_hash, new_password):
                return apology("new password and current are the same", 403)

            # Update password
            db.execute("UPDATE users SET hash = ? WHERE id = ?;", generate_password_hash(new_password), session["user_id"])

        # Success message
        flash('Username changed!') if new_username else flash('Password changed!')

        return redirect("/profile")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("profile.html", username=username)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Search for the stock
        stock = lookup(symbol)

        # Ensure there is a stock with that symbol
        if not stock:
            return apology("invalid symbol", 400)

        # Shows stock name and price
        return render_template("quoted.html", stock=stock)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure username is unique
        elif len(db.execute("SELECT username FROM users WHERE username = ?;", username)):
            return apology("username already in use", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure password has atleast 8 characters
        elif not len(password) >= 8:
            return apology("password need atleast 8 characters", 400)

        # Ensure password and confirmation are the same
        elif not password == confirmation:
            return apology("passwords must be the same", 400)

        # Insert the new user into users and store a hash of the user’s password
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", username, generate_password_hash(password))

        # Success message
        flash('Registered!')

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Search for the stock
        stock = lookup(symbol)

        # Ensure there is a stock with that symbol
        if not stock:
            return apology("invalid symbol", 400)

        # Ensure shares was submitted
        elif not shares:
            return apology("missing shares", 400)

        # Ensure shares is a positive number
        elif not shares.isdigit() or int(shares) < 1:
            return apology("invalid shares", 400)

        stocks = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?;", session["user_id"], symbol)

        # Ensure user has that stock
        if not len(stocks):
            return apology("symbol not owned", 400)

        # Ensure user has enough shares
        elif not stocks[0]["shares"] >= int(shares):
            return apology("too many shares", 400)

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]["cash"]
        shares_total_price = stock["price"] * int(shares)

        # Insert the new selling into transactions, along with the stock symbol and price
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, type) VALUES (?, ?, ?, ?, 'sale');",
                   session["user_id"], stock["symbol"], stock["price"], shares)

        # Subtract the stocks selled if after the selling the quantity is bigger than zero
        if stocks[0]["shares"] - int(shares) >= 1:
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?;",
                       stocks[0]["shares"] - int(shares), session["user_id"], stock["symbol"])
        # Delete if it's zero
        else:
            db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol = ?;", session["user_id"], stock["symbol"])

        # Add user cash earned by that selling
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", user_cash + shares_total_price, session["user_id"])

        # Success message
        flash('Sold!')

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        stocks = db.execute("SELECT symbol FROM stocks WHERE user_id = ?;", session["user_id"])
        return render_template("sell.html", stocks=stocks)

