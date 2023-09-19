words = set() # set finds and removes duplicates from the list

def check(word):
    if word.lower() in words:
        return True
    
    return False

def load(file_name):
    input_file = open(file_name, "r")
    for line in input_file:
        word = line.strip()
        words.add(word)

    input_file.close()

    return True

def size():
    len(words)

def unload():
    return True # Py unloads automatically