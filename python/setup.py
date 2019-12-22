#!/usr/bin/env python
import os
from distutils.core import setup, Extension
from gamegen import generate

try:
    os.mkdir("build")
except OSError:
    pass
module_fname = os.path.join("build", "game-module-binding.cc")
with open(module_fname, "wt") as file_:
    print("Generating file {}".format(module_fname))
    generate(file_)

mymodule = Extension('Game',
                     sources = [module_fname, '../src/Game.cc'],
                     include_dirs=['../include'])

setup(name='PyBindGen-example',
      version="0.0",
      description='PyBindGen example',
      author='xxx',
      author_email='yyy@zz',
      ext_modules=[mymodule],
     )

