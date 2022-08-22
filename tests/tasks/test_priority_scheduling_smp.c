/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "unity.h"
#include "test_macros.h"

#if ( ( configNUM_CORES > 1 ) && ( configRUN_MULTIPLE_PRIORITIES == 1 ) )

/* ------------------------------------------------------------------------------------------------------------------ */

    /*
    Task scheduling: Priority scheduling SMP

    Requires:
        - ( configNUM_CORES > 1 ) && ( configRUN_MULTIPLE_PRIORITIES == 0 )

    Purpose:
        - Test that the SMP scheduler always schedules the highest priority task for each core

    Procedure:
        - Raise the unityTask priority to (configMAX_PRIORITIES - 1)
        - unityTask creates a lower priority task for each core
            - task_A (configMAX_PRIORITIES - 2) for each core
            - task_B (configMAX_PRIORITIES - 3) for each core
        - unityTask blocks until all of the task_A runs have run
        - Clean up and restore unityTask's original priority

    Expected:
        - All of the task_As should be run by the scheduler
        - None of the task_Bs should have run
    */

    static BaseType_t task_A_ran[configNUM_CORES];
    static BaseType_t task_B_ran[configNUM_CORES];
    static SemaphoreHandle_t task_A_done_sem;

    static void task_A(void *arg)
    {
        BaseType_t task_idx = (BaseType_t) arg;

        task_A_ran[task_idx] = pdTRUE;
        /* Indicate to the unityTask that task_A has ran */
        xSemaphoreGive(task_A_done_sem);
        /* Keeping spinning to prevent the lower priority task_B from running */
        while (1) {
            ;
        }
    }

    static void task_B(void *arg)
    {
        /* The following should never be run due to task_B having a lower priority */
        BaseType_t task_idx = (BaseType_t) arg;

        task_B_ran[task_idx] = pdTRUE;
        while (1) {
            ;
        }
    }

    TEST_CASE("Tasks: Priority scheduling (SMP)", "[freertos]")
    {
        TaskHandle_t task_A_handles[configNUM_CORES];
        TaskHandle_t task_B_handles[configNUM_CORES];
        memset(task_A_ran, pdFALSE, sizeof(task_A_ran));
        memset(task_B_ran, pdFALSE, sizeof(task_B_ran));
        task_A_done_sem = xSemaphoreCreateCounting(configNUM_CORES, 0);

        /* Raise the priority of the unityTask */
        vTaskPrioritySet(NULL, configMAX_PRIORITIES - 1);

        /* Create task_A and task_B for each core */
        for (UBaseType_t x = 0; x < configNUM_CORES; x++) {
            xTaskCreate(task_A, "task_A", configTEST_STACK_SIZE, (void *)x, configMAX_PRIORITIES - 2, &task_A_handles[x]);
            xTaskCreate(task_B, "task_B", configTEST_STACK_SIZE, (void *)x, configMAX_PRIORITIES - 3, &task_B_handles[x]);
        }

        /* Block until all of the task_As have run */
        for (UBaseType_t x = 0; x < configNUM_CORES; x++) {
            xSemaphoreTake(task_A_done_sem, portMAX_DELAY);
        }

        /* Check that all the task_As have run, and none of the task_Bs have run */
        for (UBaseType_t x = 0; x < configNUM_CORES; x++) {
            TEST_ASSERT_EQUAL(pdTRUE, task_A_ran[x]);
            TEST_ASSERT_EQUAL(pdFALSE, task_B_ran[x]);
        }

        /* Cleanup */
        for (UBaseType_t x = 0; x < configNUM_CORES; x++) {
            vTaskDelete(task_A_handles[x]);
            vTaskDelete(task_B_handles[x]);
        }
        vSemaphoreDelete(task_A_done_sem);

        /* Restore the priority of the unityTask */
        vTaskPrioritySet(NULL, configTEST_UNITY_TASK_PRIORITY);
    }

#endif /* ( configNUM_CORES > 1 ) && ( configRUN_MULTIPLE_PRIORITIES == 1 ) */
