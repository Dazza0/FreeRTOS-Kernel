/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"
#include "test_macros.h"

#if ( ( INCLUDE_vTaskPrioritySet == 1 ) && ( configUSE_PREEMPTION == 1 ) && ( configNUM_CORES > 1 ) && ( configUSE_CORE_AFFINITY == 1 ) )

/* ------------------------------------------------------------------------------------------------------------------ */

    /*
    Tasks: vTaskPrioritySet can preempt (SMP)

    Requires:
        - ( INCLUDE_vTaskPrioritySet == 1 ) && ( configUSE_PREEMPTION == 1 ) && ( configNUM_CORES > 1 ) && ( configUSE_CORE_AFFINITY == 1 )

    Purpose:
        - Test that raising the priority of a task_A pinned to core X will preempt a task_B that is also pinned to core X

    Procedure:
        - Create a lower priority task_A (configTEST_UNITY_TASK_PRIORITY - 1) pinned to core X
        - Create a higher priority task_B (configTEST_UNITY_TASK_PRIORITY) pinned to core X
        - Raise the priority of task_A to (configTEST_UNITY_TASK_PRIORITY + 1)

    Expected:
        - task_A should preempt task_B
    */


    TEST_CASE("Tasks: vTaskPrioritySet can preempt (SMP)", "[freertos]")
    {
        // Todo
    }

/* ------------------------------------------------------------------------------------------------------------------ */

    /*
    Tasks: vTaskPrioritySet can yield (SMP)

    Requires:
        - ( INCLUDE_vTaskPrioritySet == 1 ) && ( configUSE_PREEMPTION == 1 ) && ( configNUM_CORES > 1 ) && ( configUSE_CORE_AFFINITY == 1 )

    Purpose:
        - Test that lowering the priority of the current task of another core will cause the task to yield

    Procedure:
        - Create a higher priority task_A (configTEST_UNITY_TASK_PRIORITY + 1) pinned to core X. It should run immediately
        - Create a lower priority task_B (configTEST_UNITY_TASK_PRIORITY) pinned to core X.
        - Signal task_A to lower its priority to (configTEST_UNITY_TASK_PRIORITY - 1)

    Expected:
        - task_A should yield to task_B
    */

    TEST_CASE("Tasks: vTaskPrioritySet can yield (SMP)", "[freertos]")
    {
        //Todo
    }

#endif /* ( INCLUDE_vTaskPrioritySet == 1 ) && ( configUSE_PREEMPTION == 1 ) && ( configNUM_CORES > 1 ) && ( configUSE_CORE_AFFINITY == 1 ) */
