
                ##### Statement 9##### 

# Complete the program to display the faulty robots.#
#hints: MAN GOOGLE: statut#

robots = {"Alpha": "ok", "Beta": "faulty", "Gamma": "ok", "Zeta": "faulty"}

faulty = [name for name, statut in robots.items() if statut == "faulty"]
print("Faulty Robots :", ", ".join(falty))