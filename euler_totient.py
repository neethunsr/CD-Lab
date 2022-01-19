def euler_totient(num):
    arr = []
    for count in range(num + 1):
        arr.append(count)
    for count in range(2, num + 1):
        if arr[count] == count:
            for j in range(count, num + 1, count):
                arr[j] -= (arr[j] / count)
    return int(arr[num])


num = 1716
print("Eulers Totient Function for {} is {}".format(num, euler_totient(num)))
