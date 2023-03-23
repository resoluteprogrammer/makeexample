import sys
import json
import random
army = {"soldiers":[], "strength":0}
soldiers = []
for i in range(1,len(sys.argv)):
    with open(sys.argv[1],"r") as soldierfile:
        soldier = json.loads(soldierfile.read())
    army["soldiers"].append(soldier)
    army["strength"] += soldier["strength"]

with open("army","w") as outfile:
    outfile.write(json.dumps(army))