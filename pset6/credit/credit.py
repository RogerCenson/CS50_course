amex = 1,
mastercard = 2,
visa = 3,
invalid = 4

def main():
    # Get credicard
    while 1:
        credicard = input("Number: ")
        if credicard.isdigit():
            credicard = int(credicard)
            if credicard != 0:
                break


    credicard_str = str(credicard)
    digits = len(credicard_str)
    is_multiply = 0
    cred_type = 0
    ret = 0
    for ii in range(digits-1, -1, -1):
        helper = 0
        if is_multiply:
            helper = 2 * int(credicard_str[ii])
            if helper >= 10:
                ret = ret + (helper % 10) + 1
            else:
                ret = ret + helper

            is_multiply = 0;
        else:
            ret = ret + int(credicard_str[ii])
            is_multiply = 1

    if (ret % 10) != 0:
        cred_type = invalid

    cred_type = getType(credicard_str, cred_type, digits)
    printfType(cred_type)

def printfType(cred_type):
        if cred_type == amex:
            print("AMEX")
        elif cred_type == visa:
            print("VISA")
        elif cred_type == mastercard:
            print("MASTERCARD") 
        elif cred_type == invalid:
            print("INVALID")

def getType(credicard_str, cred_type, digits):
    if (cred_type != invalid):
        if (credicard_str[0] == '4'):
            if (digits == 13 or digits == 16):
                cred_type = visa
            else:
                cred_type = invalid;
        elif ((credicard_str[0] == '3') and
                 ((credicard_str[1] == '4') or
                  (credicard_str[1] == '7'))):
            if (digits == 15):
                cred_type = amex
            else:
                cred_type = invalid;
        elif ((credicard_str[0] == '5') and ((credicard_str[1] == '1') or
               (credicard_str[1] == '2') or (credicard_str[1] == '3') or
               (credicard_str[1] == '4') or (credicard_str[1] == '5'))):
            if (digits == 16):
                cred_type = mastercard
            else:
                cred_type = invalid
        else:
            cred_type = invalid

    return cred_type

main()