zephyr_library()
zephyr_library_sources(src/splitsense_matrix.c)

zephyr_include_directories(${ZEPHYR_BASE}/../zmk/app/include)
zephyr_library_include_directories(${ZEPHYR_BASE}/../zmk/app/include)
