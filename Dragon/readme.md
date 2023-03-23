You have the following task.
Make a makefile that build your army to defeat the dragon.

You must follow the following steps:

1) create a vilage
2) recuit villagers to your cause
3) train the villagers
4) assemble your army 
5) attack the dragon.

The following scripts will help you:
village.py writes the list of villagers to village
recuit.py <village file> <villager name> <output file name>: generates a recuit file
train.py <recruit file> : greates a soldier file (.soldier) from the recruit file.
makearmy.py <list of soldiers> : creates an army file from soldier files writes output to "army" file
attack.py : makes attack using army file and writes result to result file.