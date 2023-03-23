import sys
import json
import random
if len(sys.argv) < 4:
    print("insufficient arguments. Expects <Village file> <'Villager name'> <output file name>")
    sys.exit(-1)

with open(sys.argv[1],"r") as villageFile:
    village = json.loads(villageFile.read())

villagerName = sys.argv[2]
villager = [x for x in village if x['name']]

if(len(villager) == 0):
    print("villager not found")
    sys.exit(-1)

villager = villager[0]

villager['strength'] =  villager['strength'] + random.randrange(0,5)


with open(sys.argv[3],"w") as outfile:
    outfile.write(json.dumps(villager))