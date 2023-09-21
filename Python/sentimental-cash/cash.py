from cs50 import get_float

coins = {
    "quarter": 25,
    "dime": 10,
    "nickel": 5,
    "penny": 1,
}

while True:
    cash = get_float("Change Owed: ")
    if cash > 0:
        break
cash *= 100

change = 0

change += cash // coins["quarter"]
cash %= coins["quarter"]

change += cash // coins["dime"]
cash %= coins["dime"]

change += cash // coins["nickel"]
cash %= coins["nickel"]

change += cash // coins["penny"]
cash %= coins["penny"]

print(f"{change}")
