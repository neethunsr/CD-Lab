import numpy as np

IP = np.array([2, 6, 3, 1, 4, 8, 5, 7])
EP = np.array([4, 1, 2, 3, 2, 3, 4, 1])
P4 = np.array([2, 4, 3, 1])
IP_INV = np.array([4, 1, 3, 5, 7, 2, 8, 6])
S0 = np.array([[1, 0, 3, 2], [3, 2, 1, 0], [0, 2, 1, 3], [3, 1, 3, 2]])
S1 = np.array([[0, 1, 2, 3], [2, 0, 1, 3], [3, 0, 1, 0], [2, 1, 0, 3]])


def convert_to_np(text):
    arr = np.zeros(len(text))
    for i in range(len(text)):
        arr[i] = int(text[i])
    return arr


def encrypt(pT):
    arr = np.zeros(8)
    for i in range(8):
        arr[i] = pT[IP[i] - 1]
    arr1 = complex_fn(arr, key_1)
    arr1 = swap(arr1)
    arr2 = complex_fn(arr1, key_2)
    cipherText = np.zeros(8)
    for i in range(8):
        cipherText[i] = arr2[IP_INV[i] - 1]
    return cipherText


def complex_fn(ar, keyz):
    l = np.zeros(4)
    r = np.zeros(4)
    for i in range(4):
        l[i] = ar[i]
        r[i] = ar[i + 4]
    ep = np.zeros(8)

    for i in range(8):
        ep[i] = r[EP[i] - 1]
        ar[i] = bool(keyz[i]) ^ bool(ep[i])
    l_1 = np.zeros(4)
    r_1 = np.zeros(4)
    for i in range(4):
        l_1[i] = ar[i]
        r_1[i] = ar[i + 4]
    row = int("" + str(int(l_1[0])) + str(int(l_1[3])), 2)
    col = int("" + str(int(l_1[1])) + str(int(l_1[2])), 2)
    val = S0[row][col]
    str_l = bin(val).replace("0b", "")

    row = int("" + str(int(r_1[0])) + str(int(r_1[3])), 2)
    col = int("" + str(int(r_1[1])) + str(int(r_1[2])), 2)
    val = S1[row][col]
    str_r = bin(val).replace("0b", "")

    r_ = np.zeros(4)
    for i in range(2):
        c1 = str_l[i]
        c2 = str_r[i]
        r_[i] = int(c1)
        r_[i + 2] = int(c2)

    r_p4 = np.zeros(4)
    for i in range(4):
        r_p4[i] = r_[P4[i] - 1]
        l[i] = bool(l[i]) ^ bool(r_p4[i])

    output = np.zeros(8)
    for i in range(4):
        output[i] = l[i]
        output[i + 4] = r[i]
    return output


def swap(arr):
    l = np.zeros(4)
    r = np.zeros(4)

    for i in range(4):
        l[i] = arr[i]
        r[i] = arr[i + 4]

    output = np.zeros(8)
    for i in range(4):
        output[i] = r[i]
        output[i + 4] = l[i]

    return output


plainText = input("Plain Text : ")
plainText = convert_to_np(plainText)
key = input("Key : ")
key = convert_to_np(key)
key_1 = input("Key 1 : ")
key_1 = convert_to_np(key_1)
key_2 = input("Key 2 : ")
key_2 = convert_to_np(key_2)

cipherText = encrypt(plainText)
ans = ""
for i in range(8):
    ans += str(int(cipherText[i]))
print("cipher Text : {0}".format(ans))
