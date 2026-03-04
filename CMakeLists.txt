zephyr_library()
zephyr_library_sources(src/splitsense_matrix.c)
# Подгружаем заголовочные файлы из основного ядра ZMK
# Условие if нужно чтобы это не крашилось, если модуль собирают изолированно
if (TARGET app)
    zephyr_library_link_libraries(app)
endif()

