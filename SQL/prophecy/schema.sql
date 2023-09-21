
# Imports Houses

from cs50 import SQL

db = SQL("sqlite:///roster.db")

x = db.execute("SELECT house FROM students")

house = []

for dict in x:
    if dict['house'] not in house:
        house.append(dict['house'])

for i in range(0, 4):
    db.execute("INSERT INTO houses(id, house_name) VALUES(?, ?)", i + 1, house[i])

-------------------------------------------------------------------------------------

# Assigns houses to students

from cs50 import SQL

db = SQL("sqlite:///roster.db")

x = db.execute("SELECT house FROM students")

house = []

for dict in x:
    if dict['house'] not in house:
        house.append(dict['house'])

y = db.execute("SELECT id AS s_id, house FROM students")

for dict in y:
    h_id = house.index(dict['house']) + 1
    s_id = dict['s_id']
    db.execute("INSERT INTO assignments(student_id, house_id) VALUES(?, ?)", s_id, h_id)
