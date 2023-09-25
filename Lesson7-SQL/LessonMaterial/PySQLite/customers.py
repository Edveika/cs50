import csv
from cs50 import SQL

database = SQL("sqlite:///customers.db")

first_name = input("First name: ").strip()

# AS stores data into variable, if there was no counter variable
rows = database.execute("SELECT \"First Name\" AS name FROM customers WHERE \"First Name\" LIKE ?", first_name)

for row in rows:
    # Here we would have to print \"First Name\"
    print(row["name"])