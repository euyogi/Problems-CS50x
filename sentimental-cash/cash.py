from cs50 import get_float

# Declares our change and our minimum coins quantity needed globally.
change_owed_in_dollars = min_coins_needed = 0


def main() -> None:
    global change_owed_in_dollars, min_coins_needed

    # Makes it only accepts positive values.
    while True:
        # Asks the change owed.
        change_owed_in_dollars = get_float('Change owed: ')
        if change_owed_in_dollars > 0:
            break

    # For each type of coin calls the function.
    for coin_type in [25, 10, 5, 1]:
        calculate_min_coins_needed_for_the_change_owed(coin_type)

    # Shows on the screen the minimum amount of coins needed.
    print(min_coins_needed)


# Receives the number of the coin (25, 10, 5, 1), calculate and updates;
# the change_owed_in_dollars and the min_coins_needed accordingly.
def calculate_min_coins_needed_for_the_change_owed(coin_type: int) -> None:
    global change_owed_in_dollars, min_coins_needed

    # Converts the change owed in dollars to cents ex: (5.75 -> 575);
    # To avoid floating point imprecision, we will reconvert it later.
    change_owed_in_cents = int(change_owed_in_dollars * 100)

    # If it's possible to pay off some of the change owed with that coin.
    if change_owed_in_cents / coin_type >= 1:
        # Check how many coins can we give as change without exceed.
        coins_quantity = int(change_owed_in_cents / coin_type)

        # Sums the coins we gave.
        min_coins_needed += coins_quantity

        # Subtracts the change owed by the money we gave.
        change_owed_in_cents -= (coins_quantity * coin_type)

        # Reconvert the change owed to dollars.
        change_owed_in_dollars = (change_owed_in_cents / 100)


main()