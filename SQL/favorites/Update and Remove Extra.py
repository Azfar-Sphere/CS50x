from cs50 import SQL

db = SQL("sqlite:///favorites.db")

x = db.execute("SELECT * FROM shows ORDER BY title")

y ={}
for dict in x:
    title = dict['title']
    counts = db.execute("SELECT COUNT(*) as count FROM shows WHERE title = ?", title)
    y[title] = counts[0]['count'];

for title in y:
    counts = y[title]
    if counts > 1:
        db.execute("DELETE FROM shows WHERE title IN (SELECT * FROM shows WHERE title = ? LIMIT ?)", title, counts - 1)