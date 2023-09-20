from enum import Enum

class Cards(Enum):
    INVALID = 0,
    AMEX = 1,
    VISA = 2,
    MASTER_CARD = 3

digit_count = 16

def main():
    credit_card = int(input("Card number: "))
    card_type = get_card_type(credit_card)

    if card_type == Cards.AMEX:
        print("AMEX")
    elif card_type == Cards.MASTER_CARD:
        print("MASTERCARD")
    elif card_type == Cards.VISA:
        print("VISA")
    elif (card_type == Cards.INVALID):
        print("INVALID")

def card_is_valid(credit_card):
    cur_digit = int(credit_card % 10)
    digit_sum = 0
    step = 10
    i = 1

    while i <= 16:
        if i % 2 == 0:
            tmp_sum = int(cur_digit) * 2
            if int(tmp_sum) >= 10:
                digit_sum += int(tmp_sum % 10)
                digit_sum += int((tmp_sum / 10) % 10)
            else:
                digit_sum += int(cur_digit) * 2
        else:
            digit_sum += int(cur_digit)

        cur_digit = int((credit_card / step) % 10)

        step *= 10
        i += 1

    if digit_sum % 10 != 0:
        return False

    return True

def get_card_type(credit_card):
    first = int(str(credit_card)[0])
    second = int(str(credit_card)[1])

    if card_is_valid(credit_card) != True:
        return Cards.INVALID
    elif first == 5:
        return Cards.MASTER_CARD
    elif first == 4:
        return Cards.VISA
    elif first == 3 and second == 7:
        return Cards.AMEX

main()