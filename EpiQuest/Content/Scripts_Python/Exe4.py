
                ##### Statement 4##### 

#To solve my problem, tell me all the numbers between 1 and 100 that are both :#
#Divisible by 4 AND not divisible by 6.#
#HINTS: Something wrong about the condition!#

for number in range(1, 101):
    if nomber % 4 == 0 or number % 6 = 0:
        print(f"The number is : {number}")