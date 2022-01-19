def gcd():
    input_list = list(map(int, input("Enter two numbers: ").split(" ")))

    num1, num2 = max(input_list), min(input_list)

    assert num1 != 0 and num2 != 0

    while num2 != 0:
        num1, num2 = num2, num1 % num2

    print(f'GCD: {num1}')


gcd()
