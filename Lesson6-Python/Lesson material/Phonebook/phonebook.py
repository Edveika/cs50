import csv

# dict/dictionary/hash table
# people = {
#     "Edvinas": "12345",
#     "Artuas": "6789",
#     "Dar kazkas": "123456577898",
#     "L33p": "1337",
#     "Ir dar kazkas": "918234"
# }

name = str(input("Name: "))
phone_number = str(input("Phone number: "))

# Ensures the file is open
# a - append, adds new stuff at the bottom
with open("contacts.csv", "a") as file:
    writer = csv.writer(file)
    writer.writerow([name, phone_number])