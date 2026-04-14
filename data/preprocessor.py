lines = []

with open("airports.csv", "r") as f:
    lines = f.readlines()

with open("processed_airports.csv", "w") as f:
    f.writelines(lines)