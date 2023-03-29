/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/platform.h"
#include "hardware/pio.h"
// Our assembled program:
#include "loopback_rx.pio.h"
#include "loopback_tx.pio.h"

#define DEBUG_PRINTS 0
//#define DEBUG_PRINTS 1

int __not_in_flash_func(main(void))
{

#if DEBUG_PRINTS
    stdio_init_all();
#endif

    PIO pio_rx = pio0;
    uint offset_rx = pio_add_program(pio_rx, &loopback_rx_program);
    uint sm_rx = pio_claim_unused_sm(pio_rx, true);
    loopback_rx_program_init(pio_rx, sm_rx, offset_rx, 26);

    PIO pio_tx = pio1;
    uint offset_tx = pio_add_program(pio_tx, &loopback_tx_program);
    uint sm_tx = pio_claim_unused_sm(pio_tx, true);
    loopback_tx_program_init(pio_tx, sm_tx, offset_tx, 27);

#if DEBUG_PRINTS
    uint32_t old;
#endif
    while (true) {
        uint32_t value = pio_sm_get_blocking(pio_rx, sm_rx);
        pio_sm_put_blocking(pio_tx, sm_tx, value);
#if DEBUG_PRINTS
        if (old != value) {
            printf("%d\n", value);
            old = value;
        }
#endif
    }
}
