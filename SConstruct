# env = Environment()

# shellSources = Object(source = Split(""" main.c """))
# shell = Program(target='simple-shell', source=shellSources);



# debugEnv = Environment(CCFLAGS = '-DDEBUG=1')
# debug = debugEnv.Program(target='simple-shell-debug', source=shellSources);



# testerSources = env.Object(source = Split(""" tester.c """))
# tester = env.Program(target='tester', source = testerSources);


# optEnv = Environment(CCFLAGS = '-O2')
# dbgEnv = Environment(CCFLAGS = ['-g', '-DDEBUG=1'])

# optObj = optEnv.Object('simple-shell-opt', shellSources)
# dbgObj = dbgEnv.Object('simple-shell-dbg', shellSources)

# opt = optEnv.Program(optObj)
# dbg = dbgEnv.Program(optObj)
source_files = ['simple-shell.c']
env = Environment(CC = 'gcc')
opt = env.Clone(CCFLAGS = '-O2')
dbg = env.Clone(CCFLAGS = ['-g', '-DDEBUG=1'])

shell = env.Program('simple-shell', source_files)

o = opt.Object('ss-opt', source_files)
optimize = opt.Program(o)

d = dbg.Object('ss-dbg', source_files)
debug = dbg.Program(d)




