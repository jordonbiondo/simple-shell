

source_files = ['src/simple-shell.c']
env = Environment(CC = 'gcc', CCFLAGS=['-Wall'])

opt = env.Clone()
opt.Append(CCFLAGS = ['-O2'])

dbg = env.Clone()
dbg.Append(CCFLAGS = ['-g', '-DDEBUG=1'])

shell = env.Program('build/simple-shell', source_files)

o = opt.Object('build/ss-opt', source_files)
optimize = opt.Program(o)

d = dbg.Object('build/ss-dbg', source_files)
debug = dbg.Program(d)




