#!/bin/env python

import threading, time


class Dog(threading.Thread):
    def __init__(self, name):
        super(Dog, self).__init__()
        self._name = name

    def run(self):
        var = 1
        while var < 6:
            print self._name, ": know-wow"
            time.sleep(1)
            var += 1


class Cat(threading.Thread):
    def __init__(self, name):
        super(Cat, self).__init__()
        self._name = name

    def run(self):
        var = 1
        while var < 5:
            print self._name, ": meow"
            time.sleep(1)
            var += 1


if __name__ == "__main__":
    doggy = Dog("doggy")
    kitty = Cat("kitty");
    doggy.start()
    kitty.start()



