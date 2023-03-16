def main() -> None:
    # Gets credit card number.
    cc_number = input('Number: ').strip()

    # Checks if it's a valid credit card number by Luhn's Algorithm.
    if is_cc_number_valid(cc_number):
        # Shows on screen what type is the credit card that has that number.
        print(cc_type(cc_number))
    else:
        print('INVALID')


# Gets a number and returns true if it's a valid credit card number by Luhn's Algorithm.
def is_cc_number_valid(cc_number: str) -> bool:
    # Declares the sums outside the loops and ifs.
    sum_even_idx_digits = sum_odd_idx_digits = 0

    # Iterates over each digit in the reversed credit card number.
    for digit_idx, digit in enumerate(cc_number[::-1]):
        # The digit is actually a character until we convert it to an int.
        digit = int(digit)

        # If that digit is on an odd index, like "2" in 123.
        if digit_idx % 2 != 0:
            # Accordingly to Luhn's Algorithm we should multiply the digit to 2.
            product = digit * 2

            # And then sums the digits of that product, to the sum of all odd indexes digits products.
            sum_odd_idx_digits += product if product < 10 else 1 + (product % 10)

        # If that digit is on an even index, like "1" or "3" in 123.
        elif digit_idx % 2 == 0:
            # Adds the digit to the sum of all even indexes digits.
            sum_even_idx_digits += digit

    # Sums the two sums.
    sum_of_sums = sum_odd_idx_digits + sum_even_idx_digits

    # Accordingly to Luhn's Algorithm if the last digit of the sum is 0, it's valid.
    return True if sum_of_sums % 10 == 0 else False


# Gets a valid credit card number by Luhn's Algorithm and returns its type.
def cc_type(cc_number: str) -> str:
    len_cc_number = len(cc_number)

    # AMEX has 15 digits and starts with 34 or 37.
    if len_cc_number in [15] and cc_number[:2] in ['34', '37']:
        return 'AMEX'
    # MASTERCARD has 16 digits and starts with 51, 52, 53, 54 or 55.
    elif len_cc_number in [16] and cc_number[:2] in ['51', '52', '53', '54', '55']:
        return 'MASTERCARD'
    # VISA has 13 or 16 digits and starts with 4.
    elif len_cc_number in [13, 16] and cc_number[0] in ['4']:
        return 'VISA'
    # If none of those patterns were found, then it's invalid.
    else:
        return 'INVALID'


main()
