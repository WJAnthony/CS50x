from cs50 import get_int


def main():
    height = 0
    while (height < 1 or height > 8):
        height = int(get_int("Height of pyramid? "))

    for i in range(height):
        print_row(height - i, i + 1)
        print()
        i = i + 1


def print_row(spaces, length):
    for i in range(spaces - 1):
        print(" ", end="")

    for j in range(length):
        print("#", end="")

    print("  ", end="")

    for k in range(length):
        print("#", end="")


main()
