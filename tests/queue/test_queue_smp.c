/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"
#include "test_macros.h"

#if ( configNUM_CORES > 1 )

/* ------------------------------------------------------------------------------------------------------------------ */

    TEST_CASE("Queue: Send across cores", "[freertos]")
    {
        // Todo
    }

/* ------------------------------------------------------------------------------------------------------------------ */

    TEST_CASE("Queue: Send from ISR across cores", "[freertos]")
    {
        // Todo
    }

#endif /* configNUM_CORES > 1 */
