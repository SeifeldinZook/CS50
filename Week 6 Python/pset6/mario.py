from cs50 import get_int

while True:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break

row = 1
for i in range(h, 0, -1):
    # print("i", i)
    spaces = i - 1
    while (spaces > 0):
        print(" ", end="")
        spaces -= 1

    for j in range(row):
        print("#", end="")

    row += 1

    print()
