#File data container
titles = []
data = []

#Read file
with open("airports.csv", "r", encoding="utf-8") as f:
    lines = f.readlines()
    titles = lines[0].split(",")
    #Split into sections respecting quotes (ignores "" as it isn't relevant)
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

#Process file
for i in range(len(data)):
    #Replace airport type with int for use with enum
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

    #Add quotes to all airport names
    if not data[i][1].startswith("\""):
        data[i][1] = "\"" + data[i][1] + "\""


for i in range(10):
    print(data[i])
    
#Write file
"""
with open("processed_airports.csv", "w", encoding="utf-8") as f:
    f.writelines(lines)
"""

print(titles)