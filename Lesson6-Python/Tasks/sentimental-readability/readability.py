
def main():
    user_input = str(input("Text: "))

    grade = calc_index(user_input)
    if grade >= 16:
        grade = str("16+")

    print(f"Grade: {grade}")

def get_letter_count(text):
    count = 0
    
    for c in text:
        if str(c).isupper() or str(c).islower():
            count +=1

    return count

def get_word_count(text):
    return len(text.split())

def get_sentence_count(text):
    count = 0

    for c in text:
        # What if ... ???
        if c == '.' or c == '!' or c == '?':
            count += 1

    return count

def calc_index(text):
    letter_count = get_letter_count(text)
    word_count = get_word_count(text)
    sentence_count = get_sentence_count(text)

    return round(0.0588 * ((letter_count / word_count) * 100) - 0.296 * ((sentence_count / word_count) * 100) - 15.8)

main()