from cs50 import get_int


def main():
    while True:
        ccnumber = get_int("Credit Card Number? ")
        if (ccnumber > 0):
            break

    number_of_digits = len(str(ccnumber))
    if (number_of_digits != 13 and number_of_digits != 15 and number_of_digits != 16):
        print("INVALID")
        exit()

    t = checksum(ccnumber)
    if (t < 10):
        print("INVALID")
        exit()
    if ((t % 10) != 0):
        print("INVALID")
        exit()

    f2d = starting(ccnumber)
    if (f2d == 51 or f2d == 52 or f2d == 53 or f2d == 54 or f2d == 55):
        if (number_of_digits == 16):
            print("MASTERCARD")
            exit()
        else:
            print("INVALID")
            exit()
    if (f2d == 34 or f2d == 37):
        if (number_of_digits == 15):
            print("AMEX")
            exit()
        else:
            print("INVALID")
            exit()
    if (int(f2d / 10) == 4):
        if (number_of_digits == 13 or number_of_digits == 16):
            print("VISA")
            exit()
        else:
            print("INVALID")
            exit()
    else:
        print("INVALID")
        exit()


def checksum(ccnumber):
    sumx1 = 0
    sumx2 = 0
    i = 0
    j = 0
    rightd = 0
    leftd = 0
    totalsum = 0

    while (ccnumber > 0):
        i = int(ccnumber % 10)
        sumx1 = sumx1 + i

        ccnumber = int(ccnumber / 10)
        j = int(ccnumber % 10)

        rightd = int((j * 2) % 10)
        leftd = int((j * 2) / 10)
        sumx2 = sumx2 + rightd + leftd

        ccnumber = int(ccnumber / 10)

    totalsum = int(sumx2 + sumx1)
    return totalsum


def starting(ccnumber):
    while (ccnumber > 100):
        ccnumber = ccnumber / 10
    return int(ccnumber)


main()
