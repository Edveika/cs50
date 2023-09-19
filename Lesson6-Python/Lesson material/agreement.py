input = str(input("Do you agree?[Y/N] ")).lower()

if len(input) > 1:
    print("Input can only contain 1 letter: Y - yes or N - no")
    exit()

if input == "y":
    print("Agreed")
elif input == "n":
    print("Disagreed")