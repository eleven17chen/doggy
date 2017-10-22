#!/bin/env python

class Hello(object):
    def __init__(self, greet):
        self._greet = greet;

    def greet(self):
        print self._greet

if __name__ == "__main__":
    doggy = Hello("Hello python!")
    doggy.greet()

