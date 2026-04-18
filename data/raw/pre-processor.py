"""
'airport.csv' data file pre-processor, requires specific formatting
MAY NOT WORK ON FUTURE VERSION OF THE FILE WITHOUT ALTERATION!
"""

#File data container
headers = []
data = []

#Read file
with open("data/raw/raw_airports.csv", "r", encoding="utf-8") as f:
    lines = f.readlines()
    headers = lines[0].rstrip("\n").split(",")
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
        fields.extend(field.strip("\"").split(",")) #split coordinates
        data.append(fields)

#Update headers
headers.pop(0) #remove ident
headers.pop(-1) #remove coordinates
headers.extend(["latitude", "longitude"])

#Process file data
for i in range(len(data)):
    #Remove ident collum
    data[i].pop(0)

    #Replace airport type with int for use with enum
    types = [""
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
with open("data/airports.csv", "w", encoding="utf-8") as f:
    f.write(",".join(headers) + "\n")
    for datum in data:
        output = ""
        for i in range(len(datum)-1):
            output += str(datum[i]) + ","
        output += datum[-1]
        f.write(output)

print("File processing complete!")