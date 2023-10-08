from flask import Flask, render_template, request

# __name__ says turns this file into an application 
app = Flask(__name__)

# Means: this is what i want to happen when user visits site/
@app.route("/", methods=["POST", "GET"])
def index():
    if request.method == "GET":
        # return the index of my site
        return render_template("index.html")
    elif request.method == "POST":
        return render_template("greet.html", name=request.form.get("name", "unknown"))