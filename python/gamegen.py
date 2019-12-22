import pybindgen

def generate(file_):
    mod = pybindgen.Module('Game')
    mod.add_include('"../include/Game.hh"')
    gameclass = mod.add_class('Game')
    gameclass.add_constructor([])
    mod.generate(file_)


