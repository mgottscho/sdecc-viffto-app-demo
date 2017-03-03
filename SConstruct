# Author: Mark Gottscho <mgottscho@ucla.edu>

import os

env = Environment(ENV = {'PATH': os.environ['PATH']})
env.Replace(CC = 'riscv64-unknown-elf-gcc')
env.Append(CPPFLAGS = '-O3')
env.Append(CPPPATH = os.environ['MWG_GIT_PATH'] + '/eccgrp-riscv-memory-due-userspace-handler')
env.Append(LIBPATH = os.environ['MWG_GIT_PATH'] + '/eccgrp-riscv-memory-due-userspace-handler')
env.Append(LIBS = ['m', 'sdecc'])
env.Append(LINKFLAGS = '-T ' + os.environ['MWG_GIT_PATH'] + '/eccgrp-riscv-memory-due-userspace-handler/sdecc-riscv.ld')
sources = ['hello.c', 'sdecc_handlers.c']
env.Program(target = 'hello', source = sources)
