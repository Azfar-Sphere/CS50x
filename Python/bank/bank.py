import string

HELLO = "hello"
H = "h"

greeting = input("Greeting: ")

table = str.maketrans("", "", string.punctuation)
greeting = greeting.translate(table).lower()

words = greeting.split()

if HELLO in words:
    print("$0")
elif words[0].startswith(H):
    print("$20")
else:
    print("$100")