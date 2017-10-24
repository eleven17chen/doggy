#!/usr/bin/python3

import time

for i in range(101):
    string = 'loading... ' + str(i) + '%'
    print(string, end='') 
    print('\b' * len(string), end='', flush=True)
    time.sleep(0.2)


