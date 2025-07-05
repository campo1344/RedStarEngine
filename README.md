# <img src="docs/logo.png" width="40"> Red Star Engine  

[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg)](https://opensource.org/licenses/MIT)  
*A high-performance graphics engine for 2D/3D games, built with passion and C++20.*  

## ✨ Features  
- ✅ **SDL3 Integration** for cross-platform rendering.  
- 🎮 **Entity-Component System (ECS)** for flexible game design.  
- 🔥 **Hot-reloading** of assets (textures, shaders).  

## 🚀 Quick Start  
```bash
git clone https://github.com/tu-usuario/RedStarEngine.git  
cd RedStarEngine && mkdir build && cd build  
cmake .. && make  
./examples/basic_game  


---

### **4. Logo y Branding**  
- **Herramientas gratuitas para diseñar el logo**:  
  - [Inkscape](https://inkscape.org/) (vectorial).  
  - [Pixlr](https://pixlr.com/) (online, estilo retro).  
- **Ideas visuales**:  
  - Una **estrella roja** con un efecto de *pixel art* o líneas geométricas.  
  - Tipografía *bold* y futurista (ej: [Google Fonts: Orbitron](https://fonts.google.com/specimen/Orbitron)).  

/\
/ \
/\
| |
| * |
||


---

### **5. Configuración Inicial de CMake**  
```cmake
cmake_minimum_required(VERSION 3.12)  
project(RedStarEngine LANGUAGES CXX)  

set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

# SDL3 como dependencia  
find_package(SDL3 REQUIRED)  
add_library(RedStarEngine STATIC src/Core.cpp src/Graphics.cpp)  
target_include_directories(RedStarEngine PUBLIC include)  
target_link_libraries(RedStarEngine PRIVATE SDL3::SDL3)  

# Ejemplo de juego  
add_executable(basic_game examples/basic_game.cpp)  
target_link_libraries(basic_game PRIVATE RedStarEngine)  