from cs50 import get_string
from re import split

text = get_string("Text: ")

letters = 0
words = 1
sentences = 0

for c in text:
    if c.isalpha():
        letters += 1
    elif c.isspace():
        words += 1

sentences = len(split(r"[.!?]", text)) - 1

L = (letters / words) * 100
S = (sentences / words) * 100

index = round((0.0588 * L) - (0.296 * S) - 15.8)

if index < 1:
    print("Before Grade 1")
elif 1 < index < 16:
    print(f"Grade {index}")
elif index >= 16:
    print("Grade 16+")
