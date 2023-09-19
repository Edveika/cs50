while True:
    try:    
        height = int(input("Pyramid height: "))
        if height > 0:
            break
        else:
            print("Height must be more than 0")
    except:
        print("Integer expected")

for i in range(height):
    print("#" * (i + 1))