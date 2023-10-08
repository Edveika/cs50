from flask import Flask, render_template, request

app = Flask(__name__)

REGISTRENTS = {}
SPORTS = [
    "Basketball",
    "Frisbee",
    "Soccer"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    sport = request.form.get("sport")
    if sport not in SPORTS:
        return render_template("failure.html")
    REGISTRENTS[name] = sport
    return render_template("success.html")

@app.route("/registrents")
def registrents():
    return render_template("registrents.html", registrents=REGISTRENTS)