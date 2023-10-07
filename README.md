## memcpp
A poweful C++ include, providing the needed functions to start working with memory in Windows.

## How to use?
To start working with memory, you must create an instance of the memcpp class:
`c++
memcpp::memcpp process("hl.exe");
`

Now you can get all the process modules:
`c++
std::vector<MODULEENTRY32> modules = process.list_of_modules();
`

or just the one you need:
`c++
uintptr_t client = process.get_module_from_name("client.dll");
`

Reading and writing data is performed by appropriate methods that receive the address and value as parameters:
`c++
process.read(addr, val);
`
`c++
process.write(addr, val);
`
