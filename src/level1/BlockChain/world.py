# -- coding: utf-8 --

import time
import os
import sys
from miner import Miner
from block_chain import Block


class World(object):
    def __init__(self):
        self._miners = {}
        self._ancestor = None

    def init(self):
        # init ancestor block chain
        self._ancstor = Block.build_new_block(None, 'Hello world!')

    def reg_miner(self, miner):
        self._miners[miner.get_id()] = miner
        miner.setDaemon(True)
        miner.start()

    def unreg_miner(self, miner):
        del self._miners[miner.get_id()]
        miner.stop()

    def notify_block_chain(self, block_chain):
        for key in self._miners.keys():
            miner = self._miners[key]
            miner.receive_block_chain(block_chain)

    def print_world(self):
        var = 1
        while (var == 1):
            print("num miners: %s")%(str(len(self._miners)))
            time.sleep(1)
            os.system('clear')

if __name__ == '__main__':
    world = World()
    world.init()

    m1 = Miner(world, 1)
    m2 = Miner(world, 2)
    m3 = Miner(world, 3)

    world.reg_miner(m1)
    world.reg_miner(m2)
    world.reg_miner(m3)

    world.print_world()

    time.sleep(15)

