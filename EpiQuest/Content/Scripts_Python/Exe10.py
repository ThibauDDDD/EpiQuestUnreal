
                ##### Statement 10##### 

#This calculator may have a problem
#As now you succed all the previous exercice you are better than us
#We can't provide you int for this one.... Good luck.

def addition(a, b):
    return a + b

def soustraction(a, b):
    return a - b

def multiplication(a, b):
    return a * b

def division(a, b):
    if b != 0:
        return a / b
    else:
        return "Error: Division by zero"

a = "trolled"

def calculatrice():
    print("Choose an operation:")
    print("1. Addition")
    print("2. Subtraction")
    print("3. Multiplication")
    print("4. Division")
    
    choix = input("Enter the operation number (1/2/3/4) : ")
    
    
    print("There is no error just press play")

    if choix == '1':
        print(f"The result is : {addition(num1, num2)}")
    elif choix == '2':
        print(f"The result is : {soustraction(num1, num2)}")
    elif choix == '3':
        print(f"The result is : {multiplication(num1, num2)}")
    elif choix == '4':
        print(f"The result is : {division(num1, num2)}")
    else:
        print("Invalid choice.")


print(a)
