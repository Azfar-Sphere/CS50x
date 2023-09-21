Title Case:

from cs50 import SQL

db = SQL("sqlite:///favorites.db")

x = db.execute("SELECT title FROM shows")

for dict in x:
    title = dict['title']
    db.execute("UPDATE shows SET title = ? WHERE title LIKE ?", title.title(), title)




