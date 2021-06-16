'''
Created on Jun 14, 2021

@author:  Gabriel Dimitriu
'''
class Duck():
    def __init__(self, input_name):
        self.__name = input_name
    @property
    def name(self):
        print('inside the getter')
        return self.__name
    @name.setter
    def name(self, input_name):
        print('inside the setter')
        self.__name = input_name
        

fowl = Duck('Howard')
print(fowl.name)
fowl.name = 'Donald'
print(fowl.name)
#print(fowl.__name) # does not work is private
