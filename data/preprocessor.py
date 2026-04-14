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
                continue
            
            if not inQuotes and c == ",":
                fields.append(field)
                field == ""
            else:
                field += c
        data.append(fields)

for i in range(10):
    print(data[i])

"""
with open("processed_airports.csv", "w", encoding="utf-8") as f:
    f.writelines(lines)
"""