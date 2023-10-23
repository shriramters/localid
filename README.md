# localid

_Locally **Unique**\* IDs_

<sub><sup>\* kinda unique most of the time YMMV.</sup></sub>

## Requirements
- 64 bit compiler with C++20 support

## Installing

```bash
git clone https://github.com/shriramters/localid.git
cd localid
mkdir build && cd build
cmake ..
make -j$(nproc) # for building the example
make install # add sudo if needed, this will install it in your OS's lib installation dir
```
### Build Options

```bash
# To skip building the example
cmake .. -DLOCALID_EXAMPLE=OFF

# To install in a different prefix
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=<your-path>
```

## Usage

check `example/main.cpp` for more.

```c++
#include <localid.hpp>
#include <iostream>
int main() {
    localid id;
    std::cout << "id: " << id << '\n';

    localid<unsigned long long> big_id;
    std::cout << "big id: " << big_id << '\n';

    // show the underlying integers
    std::cout << static_cast<unsigned>(id) << " " << static_cast<unsigned long long>(big_id) << '\n';
}
```
### output
```
id: 1YUNUGD
big id: 9PBD96J2A78MR
2142989837 11217808289878483641
```


## Features

- Basically integers (can be cast to fundamental integer types)
- Hashable with `std::hash` (can be used with `unordered_map`/`unordered_set`)
- String representation that avoids letters that might look ambiguous (all digits and uppercase letters except: 'I', 'O', 'S' and 'Z')
- Comparable