zephyr_library()
zephyr_library_sources(src/splitsense_matrix.c)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../app/include)
zephyr_library_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../app/include)
