
def get_card_number():
    while True:
        try:
            card_number = input("Enter the card number: ")
            if card_number.isdigit():
                return int(card_number)
            else:
                print("Please enter a valid number.")
        except ValueError:
            print("Please enter a valid number.")

def main():
    card_number = get_card_number()
    digits = 0
    n = card_number
    first_digit = 0
    first_two_digits = 0

    while n > 0:
        if n < 10:
            first_digit = n
        if 10 <= n < 100:
            first_two_digits = n
        n //= 10
        digits += 1

    sum = 0
    n = card_number

    for i in range(digits):
        digit = n % 10
        if i % 2 == 1:
            product = digit * 2
            sum += product - 9 if product > 9 else product
        else:
            sum += digit
        n //= 10

    if sum % 10 != 0:
        print("INVALID")
    elif digits == 15 and (first_two_digits == 34 or first_two_digits == 37):
        print("AMEX")
    elif digits == 16 and (51 <= first_two_digits <= 55):
        print("MASTERCARD")
    elif (digits == 13 or digits == 16) and first_digit == 4:
        print("VISA")
    else:
        print("INVALID")

if __name__ == "__main__":
    main()





