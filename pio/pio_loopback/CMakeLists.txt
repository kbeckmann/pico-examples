add_executable(loopback_pio)

pico_generate_pio_header(loopback_pio ${CMAKE_CURRENT_LIST_DIR}/loopback_rx.pio)
pico_generate_pio_header(loopback_pio ${CMAKE_CURRENT_LIST_DIR}/loopback_tx.pio)

target_sources(loopback_pio PRIVATE loopback_pio.c)

target_link_libraries(loopback_pio PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(loopback_pio)

# add url via pico_set_program_url
example_auto_set_url(loopback_pio)

pico_enable_stdio_usb(loopback_pio 1)


