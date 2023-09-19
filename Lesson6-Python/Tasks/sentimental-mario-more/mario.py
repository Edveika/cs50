height = int(input("Height: "))

if height <= 0:
    print("Height must be more than 0")
    exit()

for i in range(height):
    # Left side
    print(" " * (height - (i + 1)), end="")
    print("#" * (i + 1), end="")

    # Gap in-between
    print(" ", end="")

    # Right side
    print("#" * (i + 1))