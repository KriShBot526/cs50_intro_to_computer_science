from cs50 import get_float


def main():
    # Making a do while loop
    while True:
        change_owed = get_float("Change owed: ")

        if change_owed >= 0:
            break

    # Converting the floating point to a three digit number for ease
    change_owed = round(change_owed * 100)
    # Setting up a count variable to keep count of number of coins
    count = 0

    # For quarter
    change_owed, count = counter(change_owed, 25, count)

    # For dimes
    change_owed, count = counter(change_owed, 10, count)

    # For nickel
    change_owed, count = counter(change_owed, 5, count)

    # For pennies
    change_owed, count = counter(change_owed, 1, count)

    print(count)


# Function to count the coins
# Change_owed is the user input
# Currency is the value of the specific coin
# Count is the number of coins
def counter(change_owed, currency, count):
    while change_owed >= currency:
        count += 1
        change_owed = change_owed - currency

    return change_owed, count


if __name__ == "__main__":
    main()
