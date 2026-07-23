
from enum import IntEnum

import importlib.machinery
import importlib.util
from pathlib import Path

from subprocess import check_output

# Import OpCode
loader = importlib.machinery.SourceFileLoader( 'CommCodes', "../controller/CommCodes.py" )
spec = importlib.util.spec_from_loader( 'CommCodes', loader )
CommCodes = importlib.util.module_from_spec( spec )
loader.exec_module( CommCodes )

def pyEnum_to_cppEnum (someEnum):
    out = "enum class {} : uint8_t {{\n".format(someEnum.__name__)
    for pair in someEnum:
        out += "  {}={},\n".format(pair.name, pair.value)
    out += "};"
    return out

with open("src/CommCodes.hpp", "w") as f:
    f.write("// File automaticaly generated, any edit will be overwritten on the next build\n\n")
    f.write("#ifndef BOP_COMMCODES_HPP\n#define BOP_COMMCODES_HPP\n\n")
    f.write("#include <stdint.h>\n\n")
    f.write(pyEnum_to_cppEnum(CommCodes.OpCode))
    f.write("\n\n")
    f.write(pyEnum_to_cppEnum(CommCodes.ErrCode))
    f.write("\n\n")
    f.write(pyEnum_to_cppEnum(CommCodes.States))
    f.write("\n\n")
    f.write("#endif")