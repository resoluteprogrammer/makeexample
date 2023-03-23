import random
import json

names = [
    "Uandil Reyzumin",
    "Rayril Elamenor",
"Fermede Keajeon",
"Tervalor Ilihorn",
"Izlisar Inageiros",
"Crafaerd Xyrxidor"
]

Village = [{"name": x, "strength": random.randint(0,20)} for x in names]

with open("village","w") as outfile:
    outfile.write(json.dumps(Village))