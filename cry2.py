def encrypt(string, key):
    result = ""
    for char in string:
        if char == " ":
            result += " "
            continue
        if ord(char) > 96:
            result += chr((ord(char) + key - 97) % 26 + 97)
        else:
            result += chr((ord(char) + key - 65) % 26 + 65)
    return result


def decrypt(string, key):
    result = ""
    for char in string:
        if char == " ":
            result += " "
            continue
        if ord(char) > 96:
            result += chr((ord(char) - key - 97) % 26 + 97)
        else:
            result += chr((ord(char) - key - 65) % 65 + 65)
    return result


String = input("Enter Plain text : ")
key = int(input("Key : "))
encrypted = encrypt(String, key)
decrypted = decrypt(encrypted, key)
print("Plain Text : ", String)
print("Encrypted : ", encrypted)
print("Decrypted : ", decrypted)
