data = []

with open("airports.csv", "r", encoding="utf-8") as f:
    lines = f.readlines()
    for i in range(1, len(lines)):
        fields = []
        field = ""
        inQuotes = False
        for c in lines[i]:
            if c == "\"":
                inQuotes = not inQuotes
            
            if not inQuotes and c == ",":
                fields.append(field)
                field = ""
            else:
                field += c
        data.append(fields)

for i in range(len(data)):
    types = [
        "balloonport", 
        "closed",
        "heliport",
        "large_airport",
        "medium_airport",
        "seaplane_base",
        "small_airport"
    ]
    data[i][0] = types.index(data[i][0])

for i in range(10):
    print(data[i])
    
"""
with open("processed_airports.csv", "w", encoding="utf-8") as f:
    f.writelines(lines)
"""