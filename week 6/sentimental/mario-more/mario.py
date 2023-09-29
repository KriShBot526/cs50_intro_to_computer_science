from cs50 import get_int

# Immitating do while loop like we use in c
while True:
    # Taking an int input from the user
    height = get_int("Height: ")

    # Condition to check whether it is between 1 to 8 inclusive
    if 0 < height < 9:
        break

# Main code
for i in range(1, height + 1):
    # To print spaces
    j = height - i

    # Printing Spaces
    print(" " * j, end="")

    # Printing bricks
    print("#" * (i), end="  ")

    # Printing second blocks
    print("#" * (i))
