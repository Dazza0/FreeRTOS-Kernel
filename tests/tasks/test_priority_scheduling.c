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
    Task scheduling: Priority scheduling

    Requires:
        - configNUM_CORES == 1

    Purpose:
        - Test that the single-core scheduler always schedules the highest priority task

    Procedure:
        - Raise the unityTask priority to (configMAX_PRIORITIES - 1)
        - unityTask creates a lower priority tasks
            - task_A (configMAX_PRIORITIES - 2)
            - task_B (configMAX_PRIORITIES - 3)
        - unityTask blocks until task_A runs
        - Clean up and restore unityTask's original priority

    Expected:
        - task_A should run after unityTask blocks
        - task_B should never have run
    */

    static BaseType_t task_A_ran;
    static BaseType_t task_B_ran;

    static void task_A(void *arg)
    {
        task_A_ran = pdTRUE;

        /* Unblock unityTask */
        xTaskNotifyGive((TaskHandle_t)arg)

        /* Wait to be deleted by unityTask */
        vTaskSuspend(NULL);
    }

    static void task_B(void *arg)
    {
        /* The following should never run due to task_B having a lower priority */
        task_B_ran = pdTRUE;
        while (1) {
            ;
        }
    }

    TEST_CASE("Tasks: Priority scheduling", "[freertos]")
    {
        TaskHandle_t task_A_handle;
        TaskHandle_t task_B_handle;
        task_A_ran = pdFALSE;
        task_B_ran = pdFALSE;

        /* Raise the priority of the unityTask */
        vTaskPrioritySet(NULL, configMAX_PRIORITIES - 1);
        /* Create task_A and task_B */
        xTaskCreate(task_A, "task_A", configTEST_STACK_SIZE, (void *)xTaskGetCurrentTaskHandle(), configMAX_PRIORITIES - 2, &task_A_handle);
        xTaskCreate(task_B, "task_B", configTEST_STACK_SIZE, (void *)xTaskGetCurrentTaskHandle(), configMAX_PRIORITIES - 3, &task_B_handle);

        /* Block until task_A runs */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        /* Test that only task_A has run */
        TEST_ASSERT_EQUAL(pdTURE, task_A_ran);
        TEST_ASSERT_EQUAL(pdFALSE, task_B_ran);

        vTaskDelete(task_A_handle);
        vTaskDelete(task_B_handle);
        /* Restore the priority of the unityTask */
        vTaskPrioritySet(NULL, configTEST_UNITY_TASK_PRIORITY);
    }

#endif /* configNUM_CORES == 1 */
