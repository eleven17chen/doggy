#!/bin/env python

class Animal(object):
    pass

class Dog(object):
    def __init__(self): pass


class Cat(object):
    def __init__(self): pass


doggy = Dog()

assert type(doggy) == Dog
# Animal: fail
assert type(doggy) == Animal
print type(doggy)
# Cat: fail
assert type(doggy) == Cat
# int: fail
assert type(doggy) == int
