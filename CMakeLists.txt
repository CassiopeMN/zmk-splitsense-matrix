zephyr_library()
zephyr_library_sources(src/splitsense_matrix.c)
# ZMK custom modules need to find ZMK headers from their parent workspace
# In the west workspace, zmk/app is parallel to zmk-splitsense-matrix
zephyr_include_directories(${ZEPHYR_BASE}/../../zmk/app/include)
zephyr_library_include_directories(${ZEPHYR_BASE}/../../zmk/app/include)
if(TARGET app)
  zephyr_library_link_libraries(app)
endif()
