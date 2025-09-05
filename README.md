# ObjectPool (C++ Template Class)

A simple and generic **Object Pool** implementation in C++ using templates.  
Built as a learning project to understand memory management and object reuse patterns in C++.

> Made by a student learning C++, open to feedback and improvements!

---

## Quick Preview

| Pool Idle (showing baseline count)         | Pool Active (objects being reused)     |
|--------------------------------------------|----------------------------------------|
| ![Idle Pool](demo/screenshots/idle_pool.png)| ![Active Pool](demo/screenshots/active_pool.gif)|

---
*Example: Pool managing 100 objects in a simple SFML demo.*

---

## Why Use This?

- Efficiently reuse objects without constant memory allocation/deallocation.
- Great for games, simulations, or any system where object reuse improves performance.
- Uses `std::vector<Object>` internally, giving:
  - **Stack behavior** for quick acquire/release (`push_back`, `pop_back`, `back`)
  - **Easy iteration** with range-based for loops.

---

## Features

- Written as a C++ template: `ObjectPool<Object>`
- Stores inactive objects in a `std::vector<Object>` stack
- `acquire()` gives you a reusable object
- `release(obj)` returns the object to the pool
- Works with any movable object type (copyable optional). For std::unique_ptr<T>, you must use std::move() when transferring ownership.

---

## Example Usage (Single Object)

```cpp
#include "ObjectPool.hpp"
#include <iostream>
#include <string>

struct MyObject {
    int id;
    MyObject(int id = 0) : id(id) {}
};

int main() {
    ObjectPool<MyObject> pool;
    //ObjectPool<MyObject> pool{100}; // Preallocate 100 objects

    // Acquire an object from the pool
    auto obj = pool.acquire();
    obj->id = 42;
    std::cout << "Using object with id = " << obj->id << "\n";

    // Return the object to the pool
    pool.release(std::move(obj));

    // Re-acquire (reuse) the object
    auto reused = pool.acquire();
    std::cout << "Reused object with id = " << reused->id << "\n";

    // Iterate over all objects in the pool
    for (auto& o : pool.getAllObjects()) {
        std::cout << o->id << "\n";
    }

    return 0;
}
```
---

## How It Works

Internally, the pool uses:

```cpp
std::vector<Object> pool;
```

It works like a **stack**:

- `acquire()` → gets from `back()` and `pop_back()`
- `release(obj)` → adds back using `push_back(obj)`

If the pool is empty, `acquire()` just creates a new object.

---

## Build Instructions

A **Makefile** is included to simplify compiling the project.

- ✅ Works on **Unix/Linux/macOS**
- ✅ Compatible with **Windows (NT)** using environments like:
  - [MinGW](https://www.mingw-w64.org/)
  - [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/en-us/windows/wsl/)
  - [Git Bash](https://gitforwindows.org/)

#### To build:

```bash
make run
```

This will compile the project using `g++` with C++17.  
You can customize the `Makefile` as needed for your system or compiler.

---

## Dependencies

The core object pool (`include/ObjectPool.hpp`) is **header-only** and has **no external dependencies**.

The demo (`demo/` folder) requires:  
- [SFML](https://www.sfml-dev.org/) (installed via MSYS2 recommended)

On MSYS2 (64-bit MinGW):

```bash
pacman -S mingw-w64-x86_64-sfml
```

---

## To-Do / Learning Goals

- [ ] Add support for custom object initialization
- [ ] Add thread-safety (maybe with mutex?)
- [ ] Benchmark vs. dynamic allocation
- [ ] Write unit tests

---

## Credits

This is a self-learning project. Thanks to tutorials, forums, and anyone sharing C++ knowledge online.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).  
If you learn something from this, that's awesome!