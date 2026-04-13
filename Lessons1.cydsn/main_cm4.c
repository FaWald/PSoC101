/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        Cy_GPIO_Write(Pin_LED3_0_PORT, Pin_LED3_0_NUM, 0u);  // LED an, falls active low
        Cy_GPIO_Write(Pin_LED4_0_PORT, Pin_LED4_0_NUM, 1u);  // LED aus
        Cy_SysLib_Delay(2000);

        Cy_GPIO_Write(Pin_LED3_0_PORT, Pin_LED3_0_NUM, 1u);  // LED aus
        Cy_GPIO_Write(Pin_LED4_0_PORT, Pin_LED4_0_NUM, 0u);  // LED an, falls active low
        Cy_SysLib_Delay(2000);
    }
}

// PORT = wo der Pin liegt
// NUM = welcher Pin es ist
// 1u = was auf den Pin geschrieben wird

/* [] END OF FILE */
