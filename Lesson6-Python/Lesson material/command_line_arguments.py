from sys import argv, exit

if len(argv) == 1:
    print("Command line args required!")
    # Sys exit allows to exit with error code
    exit(1337)

for i in argv[1:]:
    print(i)

exit(0)