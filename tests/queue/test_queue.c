/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"
#include "test_macros.h"

#if ( configNUM_CORES == 1 )

/* ------------------------------------------------------------------------------------------------------------------ */

    /*
    Queue: Send from higher to lower priority

    Requires:
        - ( configNUM_CORES == 1 )

    Purpose:
        - Test that a higher priority task can send a queue message to a lower priority task
        - Test that the higher priority sender will preempt as soon as a space is available

    Procedure:
        - Create a task_A of priority (configTEST_UNITY_TASK_PRIORITY + 2)
        - Create a task_B of priority (configTEST_UNITY_TASK_PRIORITY + 1)
        - Create a queue of length M
        - task_A calls xQueueSend N times, where N = 2M
        - task_B calls xQueueReceive N times

    Expected:
        - task_A should blocks on the first M+1 call
        - task_A should preempt as soon as task_B makes an available space on the queu
    */

    TEST_CASE("Queue: Send from higher to lower priority", "[freertos]")
    {
        // Todo
    }

/* ------------------------------------------------------------------------------------------------------------------ */

    /*
    Queue: Send from lower to higher priority

    Requires:
        - ( configNUM_CORES == 1 )

    Purpose:
        - Test that a lower priority task can send a queue message to a higher priority task
        - Test that the higher priority receiver will preempt as soon as a message is available for receiving

    Procedure:
        - Create a task_A of priority (configTEST_UNITY_TASK_PRIORITY + 1)
        - Create a task_B of priority (configTEST_UNITY_TASK_PRIORITY + 2)
        - Create a queue of length M
        - task_A calls xQueueSend N times, where N = 2M
        - task_B calls xQueueReceive N times

    Expected:
        - task_B should preempt task_A on each message
    */

    TEST_CASE("Queue: Send from lower to higher priority", "[freertos]")
    {
        // Todo
    }

#endif /* configNUM_CORES == 1 */
