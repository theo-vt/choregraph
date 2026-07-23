import importlib.machinery
import importlib.util

import tomli

def write_commcodes():

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
        f.write("#ifndef COMMCODES_HPP_\n#define COMMCODES_HPP_\n\n")
        f.write("#include <stdint.h>\n\n")
        f.write(pyEnum_to_cppEnum(CommCodes.OpCode))
        f.write("\n\n")
        f.write(pyEnum_to_cppEnum(CommCodes.ErrCode))
        f.write("\n\n")
        f.write(pyEnum_to_cppEnum(CommCodes.States))
        f.write("\n\n")
        f.write("#endif")

def write_configs():
    def write_namespace(namespace, content):
        config_content = "namespace {} {{\n\n".format(namespace)

        for key, value in content.items():
            if isinstance(value, int):
                config_content += f"constexpr int {key} = {value};\n"
            elif isinstance(value, float):
                config_content += f"constexpr float {key} = {value};\n"

        config_content += "\n}} // !{}\n\n".format(namespace)

        return config_content
    

    with open("config.toml", "rb") as input, open("src/Config.hpp", "w") as output:
        output.write("// File automaticaly generated, any edit will be overwritten on the next build\n\n")
        output.write("#ifndef CONFIG_HPP_\n#define CONFIG_HPP_\n\n")
        output.write("namespace config {\n\n")

        toml_dict = tomli.load(input)
        for namespace, content in toml_dict.items():
            output.write(write_namespace(namespace, content))

        output.write("} // !config \n\n")
        output.write("\n\n")
        output.write("#endif")


write_commcodes()
write_configs()