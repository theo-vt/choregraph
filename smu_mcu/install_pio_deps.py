Import("env")

# Install missed package
try:
    import tomli
except ImportError:
    env.Execute("$PYTHONEXE -m pip install tomli")