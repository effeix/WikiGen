# WikiGen
Random Wikipedia articles generator based on Machine Learning

## Libraries
WikiGen relies on some libraries to work. Here they are:
- [Boost 1.67.0](https://www.boost.org/)
- [pugixml 1.9](https://pugixml.org/)

To install the libraries, simply download the versions specified above and include them in their respective directories inside the ```lib/``` directory. Here is the final project tree:

```
root
    inc/
        wikigen.hpp
    lib/
        boost_1_67_0/
            <Boost files>
        pugixml-1.9/
            <pugixml files>
    src/
        wikigen.cpp
    xml/
        wikidump.xml
```