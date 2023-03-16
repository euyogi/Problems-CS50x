from re import findall


def main() -> None:
    # Gets the text from the user.
    text = input('Text: ')

    # Prints the grade level of that text.
    print(grade_level_of(text))


# Calculates and returns the grade level of a text according to the Coleman-Liau formula.
def grade_level_of(text: str) -> str:
    # Gets letters quantity with a regular expression that finds them.
    letters_quantity = len(findall(r'[a-zA-Z]', text))

    # Gets words quantity with a regular expression, including abreviated words and compound words.
    words_quantity = len(findall(r"[a-zA-Z|'|-]+", text))

    # Gets sentences quantity with a regular expression, sentences end is marked by a ".", "!" or "?" symbol.
    sentences_quantity = len(findall(r'.+?[\.|!|?]+', text))

    # Calculates "L", which is the average number of letters per 100 words in the text.
    L = (letters_quantity / words_quantity) * 100

    # Calculates "S", which is the average number of sentences per 100 words in the text.
    S = (sentences_quantity / words_quantity) * 100

    # Calculates "idx", which is the Coleman-Liau index.
    idx = 0.0588 * L - 0.296 * S - 15.8

    # If the index is less than 1.
    if idx < 1:
        return 'Before Grade 1'

    # If the index is more or equal than 16.
    elif idx >= 16:
        return 'Grade 16+'

    # If the index is between 1 and 16.
    else:
        return f'Grade {round(idx)}'


main()