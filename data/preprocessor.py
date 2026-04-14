lines = []
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

print(data[214])
print(data[2434])

"""
with open("processed_airports.csv", "w", encoding="utf-8") as f:
    f.writelines(lines)
"""