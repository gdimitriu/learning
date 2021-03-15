'''
Created on Mar 15, 2021

@author:  Gabriel Dimitriu
'''
import json

numbers = [2,3,5,7,11,13]
filename = 'numbers.json'
with open(filename, 'w') as f:
    json.dump(numbers,f)

with open(filename) as f:
    numbers = json.load(f)

print("After load")    
print(numbers)
