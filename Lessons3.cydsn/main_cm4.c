/* ========================================
 *
 * Lesson 3 - Button Interrupt für PSoC 6
 *
 * ========================================
*/
#include "project.h"

volatile uint8_t ledState = 0u;

/* Interrupt-Konfiguration für GPIO Port 0
   Pin_SW2 liegt bei dir auf P0[4], daher gpio_0_IRQn */
const cy_stc_sysint_t SW2_Interrupt_cfg =
{
    .intrSrc = ioss_interrupts_gpio_0_IRQn,
    .intrPriority = 3u
};

void SW2_ISR(void)
{
    /* Prüfen, ob wirklich Pin_SW2 den Interrupt ausgelöst hat */
    if(Cy_GPIO_GetInterruptStatusMasked(Pin_SW2_0_PORT, Pin_SW2_0_NUM) != 0u)
    {
        /* Interrupt-Flag vom Pin löschen */
        Cy_GPIO_ClearInterrupt(Pin_SW2_0_PORT, Pin_SW2_0_NUM);

        /* LED-Zustand umschalten */
        ledState = !ledState;

        if(ledState == 0u)
        {
            Cy_GPIO_Write(Pin_LED3_0_PORT, Pin_LED3_0_NUM, 1u); // Rot aus
            Cy_GPIO_Write(Pin_LED4_0_PORT, Pin_LED4_0_NUM, 0u); // Grün an
        }
        else
        {
            Cy_GPIO_Write(Pin_LED3_0_PORT, Pin_LED3_0_NUM, 0u); // Rot an
            Cy_GPIO_Write(Pin_LED4_0_PORT, Pin_LED4_0_NUM, 1u); // Grün aus
        }
    }
}

int main(void)
{
    __enable_irq();

    /* Anfangszustand */
    Cy_GPIO_Write(Pin_LED3_0_PORT, Pin_LED3_0_NUM, 1u); // Rot aus
    Cy_GPIO_Write(Pin_LED4_0_PORT, Pin_LED4_0_NUM, 0u); // Grün an

    /* GPIO-Port-Interrupt initialisieren */
    Cy_SysInt_Init(&SW2_Interrupt_cfg, SW2_ISR);

    /* Alte Pending-Interrupts löschen */
    NVIC_ClearPendingIRQ(SW2_Interrupt_cfg.intrSrc);

    /* Interrupt aktivieren */
    NVIC_EnableIRQ(SW2_Interrupt_cfg.intrSrc);

    for(;;)
    {
        /* Kein Polling mehr.
           Button wird über Interrupt behandelt. */
    }
}

/* [] END OF FILE */