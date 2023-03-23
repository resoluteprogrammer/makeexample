import sys
import os
import json
import random
if len(sys.argv) < 2:
    print("insufficient arguments. Expects <recruit file>")
    sys.exit(-1)
 
inputfile = sys.argv[1]

with open(inputfile,"r") as recruitFile:
    recruit = json.loads(recruitFile.read())


outputfile = os.path.splitext(inputfile)[0]+".soldier"
recruit['strength'] =  recruit['strength'] + random.randrange(0,5)

with open(outputfile,"w") as outfile:
    outfile.write(json.dumps(recruit))