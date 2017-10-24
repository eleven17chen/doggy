#!/bin/env python

import os
import sys
import time
while 1:
    os.write(1, "\r[%.3f]" % time.time())
#    os.write(1, "\r[%.3f]\n" % time.time())
    sys.stdout.flush()
#    os.write(1, "\b")
    time.sleep(1)
