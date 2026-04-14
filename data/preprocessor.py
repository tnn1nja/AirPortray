lines = []

with open("airports.csv", "r", encoding="utf-8") as f:
    lines = f.readlines()

with open("processed_airports.csv", "w", encoding="utf-8") as f:
    f.writelines(lines)