/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"
#include "test_macros.h"

#if ( ( INCLUDE_vTaskPrioritySet == 1 ) && ( configUSE_PREEMPTION == 1 ) && ( configNUM_CORES == 1 ) )

/* ------------------------------------------------------------------------------------------------------------------ */

    /*
    Tasks: vTaskPrioritySet can preempt

    Requires:
        - ( INCLUDE_vTaskPrioritySet == 1 ) && ( configUSE_PREEMPTION == 1 ) && ( configNUM_CORES == 1 )

    Purpose:
        - Test that raising the priority of a task_A will cause task_A to preempt the current task

    Procedure:
        - Create a task_A of priority (configTEST_UNITY_TASK_PRIORITY - 1)
        - unityTask raises the priority of task_A to (configTEST_UNITY_TASK_PRIORITY + 1)

    Expected:
        - task_A should preempt unityTask
    */

    TEST_CASE("Tasks: vTaskPrioritySet can preempt", "[freertos]")
    {
        // Todo
    }

/* ------------------------------------------------------------------------------------------------------------------ */

    /*
    Tasks: vTaskPrioritySet can yield

    Requires:
        - ( INCLUDE_vTaskPrioritySet == 1 ) && ( configUSE_PREEMPTION == 1 ) && ( configNUM_CORES == 1 )

    Purpose:
        - Test that lowering the priority of the current task will cause the task to yield

    Procedure:
        - Create a task_A of priority (configTEST_UNITY_TASK_PRIORITY + 1). It should run immediately
        - task_A will lower it's priority to (configTEST_UNITY_TASK_PRIORITY - 1)

    Expected:
        - task_A should yield to unityTask when it lowers its priority
    */

    TEST_CASE("Tasks: vTaskPrioritySet can yield", "[freertos]")
    {
        //Todo
    }

#endif /* ( INCLUDE_vTaskPrioritySet == 1 ) && ( configUSE_PREEMPTION == 1 ) && ( configNUM_CORES == 1 ) */
