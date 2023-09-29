import re
from cs50 import get_string


def main():
    text = get_string("Text: ")

    # Counts the number of letters
    letters = len(re.findall("[a-zA-Z]", text))

    # Counts the number of words
    words = len(text.split())

    # Counts the number of sentences
    sentences = len(re.findall(r"[.!?]+", text))

    index = readability_index(letters, words, sentences)

    print_grade(index)


def readability_index(letters, words, sentences):
    words_per_100 = words / 100

    # Average letters per 100 words
    l = letters / words_per_100

    # Average sentences per 100 words
    s = sentences / words_per_100

    # Coleman-Liau index
    index = round(0.0588 * l - 0.296 * s - 15.8)

    return index


# Prints the grade of the text
def print_grade(index):
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
