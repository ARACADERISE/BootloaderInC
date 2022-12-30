import subprocess, os

subprocess.run('sudo mv something.h /usr/lib/gcc/x86_64-linux-gnu/9/include/',
        shell=True,
        cwd=os.getcwd())
