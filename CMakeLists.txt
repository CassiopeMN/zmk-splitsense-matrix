zephyr_library()
zephyr_library_sources(src/splitsense_matrix.c)

# ZMK custom modules need to find ZMK headers from their parent workspace.
# In the GitHub Actions builder, ZEPHYR_BASE is /tmp/zmk-config/zephyr
# and the ZMK app is at /tmp/zmk-config/zmk/app.
zephyr_include_directories(${ZEPHYR_BASE}/../zmk/app/include)
zephyr_library_include_directories(${ZEPHYR_BASE}/../zmk/app/include)
