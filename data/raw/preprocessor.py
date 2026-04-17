#File data container
titles = []
data = []

#Read file
with open("airports.csv", "r", encoding="utf-8") as f:
    lines = f.readlines()
    titles = lines[0]
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
        fields.append(field)
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

    #Add quotes to all airport and municiplaity names for easier parsing
    for j in (1,6):
        if not data[i][j].startswith("\""):
            data[i][j] = "\"" + data[i][j] + "\""

#Write file
def toLine(arr):
    output = ""
    for i in range(len(arr)-1):
        output += str(arr[i]) + ","
    output += arr[-1]
    return output

with open("processed_airports.csv", "w", encoding="utf-8") as f:
    f.write(titles)
    for datum in data:
        f.write(toLine(datum))

print("file processed")