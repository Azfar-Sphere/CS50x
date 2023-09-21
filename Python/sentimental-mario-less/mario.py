while True:
    try:
        height = int(input("Height: "))
        if 0 < height <= 8:
            break
    except ValueError:
        print("Invalid Value, please enter an Integer from 1-8")


j = 1
for i in range(height):
    for i in range(height - j):
        print(" ", end="")
    print("#" * j)
    j += 1
