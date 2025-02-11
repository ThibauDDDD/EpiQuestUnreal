robots = {"Alpha": "ok", "Beta": "faulty", "Gamma": "ok", "Zeta": "faulty"}

#solution
faulty = [nom for nom, statut in robots.items() if statut == "faulty"]
print("Faulty Robots :", ", ".join(faulty))