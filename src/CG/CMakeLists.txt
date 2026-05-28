add_library(CG
    src/Polygon/Polygon.cpp
    src/RNG/RNG.cpp

    src/CG.cpp
)

target_include_directories(CG PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)