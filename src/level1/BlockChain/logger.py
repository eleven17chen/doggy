# -- coding: utf-8 --

import logging
# from global_var import *

LOG_LEVEL = logging.DEBUG

LOGGERS = {}

# 开发一个日志系统， 既要把日志输出到控制台， 还要写入日志文件
class Logger(object):
    def __init__(self, logname):
        self._logname = logname
        if (LOGGERS.has_key(logname)): pass
        else:
            logger = logging.getLogger(logname)
            logger.setLevel(LOG_LEVEL)
            LOGGERS[logname] = logger

            ch = logging.StreamHandler()
            ch.setLevel(LOG_LEVEL)
            formatter = logging.Formatter('[%(asctime)s][%(levelname)s][' + str(logname) + ']: %(message)s')
            ch.setFormatter(formatter)

            # 给logger添加handler
            logger.addHandler(ch)
            logger.info('hhhhh')

    def log(self):
        return LOGGERS[self._logname]

if __name__ == "__main__":
    logger = Logger('ins1')
    logger = Logger('ins1')
    logger2 = Logger('ins2')
    logger.log().info("abc")
    logger.log().error("long" + " term " + str(1))

