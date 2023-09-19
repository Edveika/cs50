import my_print

def main():
    try:
        x = int(input())
        y = int(input())
        z = divide(x, y)
    except:
        # Uses a .py file to print that i created
        my_print.print("Integer expected")
        exit()

    print(f"{z:.50f}")

def add(x, y):
    return x + y
    
def divide(x, y):
    return x / y

main()