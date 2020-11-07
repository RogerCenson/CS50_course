def main():
    grade = 0
    ii = 0
    nLetters = 0
    nWords = 1
    nSentences = 0
    text = input("text: ")
    size = len(text)
    # print("text: ")
    # scanf("%[^\n]", text)

    while (ii < size):
        if (text[ii].isalpha()):
            nLetters =  nLetters + 1
        elif (text[ii - 1] != ' ' and text[ii] == ' ' and text[ii + 1] != ' '):
            nWords = nWords + 1
        elif (text[ii] == '.' or text[ii] == '!' or text[ii] == '?'):
            nSentences = nSentences + 1
        ii = ii + 1

    grade = 0.0588 * ((100 * nLetters) / nWords) - 0.296 * ((100 * nSentences) / nWords) - 15.8
    # print("%f letter(s)\n", nLetters)
    # print("%f word(s)\n", nWords)
    # print("%f sentence(s)\n", nSentences)
    printGrade(grade)

def printGrade(grade):
    if (grade < 1):
        print("Before Grade 1")
    elif (grade > 16):
        print("Grade 16+")
    else:
        print("Grade", (int(round(grade))))

main()