import sys
import random
from pyfiglet import Figlet

figlet = Figlet()
fonts = figlet.getFonts()


def main():
    argc = len(sys.argv) - 1
    if argc != 0 and argc != 2:
        exit()

    if argc == 2:
        if sys.argv[1] not in ["-f", "-font"]:
            exit()

        if sys.argv[2] not in fonts:
            exit()

    f = sys.argv[2] if argc == 2 else random.choice(fonts)

    text = input("Input: ")

    figlet.setFont(font=f)
    print(figlet.renderText(text))


def exit():
    print("Invalid Usage!")
    sys.exit(1)


main()
