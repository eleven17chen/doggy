#!/bin/env python
# -- coding: utf-8 --

import hashlib, time
from logger import Logger
from global_var import *

DEBUG=1

class Block(object):
    def __init__(self, ancestor, hash, content):
        self._ancestor = self
        if (ancestor):
            self._ancestor = ancestor
        self._hash     = hash
        self._content  = content
        self._log = Logger('block')

    def get_hash(self):
        return self._hash

    def get_content(self):
        return self._content

    def get_ancestor(self):
        return self._ancestor

    def str(self):
        str = ""
        str += "ancestor : " + self._ancestor.get_hash().__str__() + "\n"
        str += "content  : " + self._content + "\n"
        str += "hash     : " + self._hash + "\n\n"
        return str

    @classmethod
    def get_ancestor_hash(self):
        hash = hashlib.sha256("Hello doggy!").hexdigest();
        return hash

    @classmethod
    def gen_new_hash(self, pre_hash, content):
        if (DEBUG == 0):
            time.sleep(3)
        x = pre_hash + content;
        hash = hashlib.sha256(x).hexdigest();
        return hash

    @classmethod
    def build_new_block(self, pre_block, content):
        block = None
        if (pre_block):
            hash = Block.gen_new_hash(pre_block.get_hash(), content)
            block = Block(pre_block.get_ancestor(), hash, content)
        else:
            hash = Block.get_ancestor_hash()
            block = Block(None, hash, content)
        return block


class FakeBlock(Block):
    def __init__(self, pre_block, content):
        x = None;
        ancestor = None;

        if (pre_block):
            x = pre_block.get_hash() + content
            ancestor = pre_block.get_ancestor()
        else:
            x = Block.get_ancestor_hash() + content

        hash = hashlib.sha256(x).hexdigest()
        super(FakeBlock, self).__init__(ancestor, hash, content)


class BlockNode(object):
    def __init__(self, block):
        self._pre_bn  = None
        self._next_bn = None
        self._block = block;

    def set_pre(self, pre_bn):
        self._pre_bn = pre_bn

    def set_next(self, next_bn):
        self._next_bn = next_bn

    def set_block(self, block):
        self._block = block

    def get_block(self):
        return self._block

    def get_next_bn(self):
        return self._next_block

    def get_pre_bn(self):
        return self._pre_bn


    def str(self):
        str = self._block.str();
        if (self._pre_bn):
            str += self._pre_bn.str()

        return str


class BlockChain(object):
    def __init__(self):
        self._head_bn = None
        self._len = 0

    def append(self, block):
        bn = BlockNode(block)
        if (self._head_bn):
            bn.set_pre(self._head_bn)
            self._head_bn.set_next(bn)
        else:
            self._head_bn = bn

        self._len += 1

    def get_head(self):
        block = None
        if (self._head_bn):
            block = self._head_bn.get_block();
        return block

    def contain(self, bc):
        if (self._head and self._head.get_ancestor() == self._head.get_ancestor()):
            return True
        else:
            return False

    def get_len(self):
        return self._len;


    def str(self):
        str = ''
        str += "length: " + str(self._len)
        if (self._head_bn):
            str = self._head_bn.str()
        else:
            str = "Empty chain"
        return str;



class BlockManager(object):
    def __init__(self):
        self._bn_heads = []

    # 放一个链进来，如果涟已经存在，则返回
    def put(self, block_node):
        self._bn_heads.append(block_node)


    # 取链最长的BLockChain的HEAD
    def get(self):
        head = None
        if self._bn_heads:
            head = self._bn_heads[1]
        return head

def test_bc():
    b1 = FakeBlock(None, "b1");
    bn1 = BlockNode(b1)

    b2 = FakeBlock(b1, "b2");
    bn2 = BlockNode(b2)

    b3 = FakeBlock(b2, "b3");
    bn3 = BlockNode(b3)

    bn1.set_next(bn2)
    bn2.set_pre(bn1)

    bn2.set_next(bn3)
    bn3.set_pre(bn2)

    bc = BlockChain()
    bc.set_head_bn(bn3)

#    print "bn1 info"
#    print bn1.__str__()
#    print bn1.get_pre_bn().__str__()
#
#    print "bn2 info"
#    print bn2.__str__()
#    print bn2.get_pre_bn().__str__()
#
#    print "bn3 info"
#    print bn3.__str__()
#    print bn3.get_pre_bn().__str__()

    print bc.str()


if __name__ == "__main__":
    test_bc()

        
