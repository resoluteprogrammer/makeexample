import json

with open("army", "r") as armyfile:
    army = json.loads(armyfile.read())


with open("result", "w") as outfile:
    if(army["strength"]> 50):
        outfile.write("You defeated the dragon")
    else:
        outfile.write("you were defeated")