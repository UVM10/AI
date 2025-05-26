from math import sqrt

def so_nguyen_to(a):
    if a < 2:
        print(f"{a} is not a prime number")
        return 
    for i in range(2, int(sqrt(a))):
        if not (a%i):
            print(f"{a} is not a prime number")
            break
    else:
        print(f"{a} is a prime number")
x = int(input())
so_nguyen_to(x)