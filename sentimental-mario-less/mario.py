from cs50 import get_int




while True:
    height = get_int("enter a number: ")
    if 1 <= height <= 8:
        break

for i in range (1, height+1):
        print(" " * (height - i) + "#"* i)

