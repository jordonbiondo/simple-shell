env = Environment()

shellSources = env.Object(source = Split("""
main.c

"""))

shell = env.Program(target='simple-shell', source = shellSources);

Default(shell)

testerSources = env.Object(source = Split("""
tester.c
"""))
tester = env.Program(target='tester', source = testerSources);
