from cs50 import SQL

db = SQL("sqlite:///favorites.db")
favorite = input("Favortie: ")

rows = db.execute ("SELECHT COUNT (*) AS n FROM favorites WHERE language = ?", favorite)
row = row[0]

print(row["n"])
