from cs50 import get_string


def main():
    text = get_string("Input text: ")

    letters_per_100 = count_letters(text) / count_words(text) * 100.0
    sentences_per_100 = count_sentences(text) / count_words(text) * 100.0

    coleman_liau = (0.0588 * letters_per_100) - (0.296 * sentences_per_100) - 15.8
    grade = round(coleman_liau)

    if (grade < 1):
        print("Before Grade 1")
        exit()

    if (grade > 16):
        print("Grade 16+")
        exit()
    else:
        print(f"Grade {grade}")
        exit()


def count_letters(text):
    sum_letters = 0
    for i in range(len(str(text))):
        a = ord(text[i].upper())
        if (a >= 65 and a <= 90):
            sum_letters = sum_letters + 1
    return sum_letters


def count_words(text):
    sumspaces = 0
    for i in range(len(str(text))):
        a = ord(text[i])
        if (a == 32):
            sumspaces = sumspaces + 1
    return sumspaces + 1


def count_sentences(text):
    sumsentences = 0
    for i in range(len(str(text))):
        a = ord(text[i])
        if (a == 33 or a == 46 or a == 63):
            sumsentences = sumsentences + 1
    return sumsentences


main()
