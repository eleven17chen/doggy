# -- coding: utf-8 --

import threading, time
from logger import Logger
from global_var import *

from block_chain import Block
from block_chain import BlockChain
from logger import Logger

class Miner(threading.Thread):
    def __init__(self, world, id):
        super(Miner, self).__init__()
        self._world = world
        self._id = id
        self._dig_times = 0
        self._log = Logger('miner')
        # self._chains = []
        self._work_chain = BlockChain()
        self._stop = False

    def get_id(self):
        return self._id

    def run(self):
        # do dig
        self._log.log().debug('Starting miner')
        self.dig()

    def dig(self):
        var = 1
        while (var == 1):
            self._dig_times = self._dig_times + 1
            self._log.log().debug("miner[" + str(self._id) + "]: digging " + str(self._dig_times))
            if (self._stop):
                break;
            curr_chain = self._work_chain
            time.sleep(1)
            # 检查_work_chain是否变化了。
            if (curr_chain != self._work_chain):
                continue

            content = "miner[" + str(self._id) + "]: dig[" + str(self._dig_times) + "]"
            preblock = self._work_chain.get_head()
            new_block = Block.build_new_block(preblock, content)

            # 需要与receive block chain互斥
            self._work_chain.append(new_block)
            self._world.notify_block_chain(self._work_chain)

    def stop(self):
        self._stop = True

    def receive_block_chain(self, block_chain):
        # find = False
        # for chain in self._chains:
        #     if (block_chain.get_head() == chain.get_head()):
        #         find = True
        #
        # if (find == False):
        #     self._chains.append(block_chain);
        #     if (chain.get_len() - self._work_chain.get_len() > 1):
        #         self._work_chain = block_chain

        self._log.log().debug("miner[" + str(self._id) + "]: receive a block chain ")
        if (block_chain.get_len() - self._work_chain.get_len() > 1):
            self._work_chain = block_chain


# if __name__ == "__main__":
#     miner = Miner(1)
#     miner.start()
    # miner.receive_block(bn)
    # miner.notify_block()
