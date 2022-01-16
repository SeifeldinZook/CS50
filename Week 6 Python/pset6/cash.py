from cs50 import get_float

coins = 0
quarters = 25
dimes = 10
nickels = 5
pennies = 1

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break
    
cents = round(change * 100)

for i in range(cents, 0, -1):
    if cents == 0:
        break
    elif (cents >= quarters):
        cents = cents - quarters
    elif (cents >= dimes):
        cents = cents - dimes
    elif (cents >= nickels):
        cents = cents - nickels
    else:
        cents = cents - pennies
    
    coins += 1

print(coins)