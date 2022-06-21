/**
 * @author [Marek Jordán]
 * @create date 15-04-2022 - 16:46:28
 * @modify date 01-06-2022 - 21:34:53
 * @desc [Časomíra]
 */
#include "stm8s.h"
#include "stm8s_milis.h"
#include "stm8s_4segment.h" // Knihovna pro 4 dgt 7 segment

// https://github.com/jindramachka/MIT/blob/master/%C4%8Dasova%C4%8D/app/src/main.c - jindruv casovac

// Proměnné pro časomíru
bool status = FALSE;
int sec = 0;
int min = 0;
uint32_t mtime_key = 0;

// Makro pro laser
#define port_laser GPIOA
#define pin_laser PIN_6
#define laser_read GPIO_ReadInputPin(port_laser, pin_laser)

// Makro pro tlačítka
#define button1_read (GPIO_ReadInputPin(GPIOA, PIN_4))
#define button2_read (GPIO_ReadInputPin(GPIOA, PIN_5))

// Makro pro bzučák
#define port_buzzer GPIOG
#define pin_buzzer PIN_2

// Funkce pro bzučák (buzzer(TRUE) - zapnout bzučák) \ (buzzer(FALSE) - vypnout bzučák)
void buzzer(bool stav)
{
    if (stav == TRUE)
    {
        GPIO_WriteHigh(port_buzzer, pin_buzzer);
    }
    else if (stav == FALSE)
    {
        GPIO_WriteLow(port_buzzer, pin_buzzer);
    }
}

int nulovani(void)
{
    sec = 0;
    min = 0;
    return min, sec;
}

void main(void)
{
    GPIO_DeInit;                                                   // Denicializace pinů
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);                 // FREQ MCU 16MHz
    Serial.begin(9600);                                            // Serial monitor Baudrate = 9600
    GPIO_Init(port_buzzer, pin_buzzer, GPIO_MODE_OUT_PP_LOW_FAST); // bzucak (PD7)
    GPIO_Init(port_laser, pin_laser, GPIO_MODE_IN_FL_NO_IT);       // LASER (PB1)
    GPIO_Init(GPIOA, PIN_4, GPIO_MODE_IN_PU_NO_IT);                // TLAC INT (PA4)
    GPIO_Init(GPIOA, PIN_5, GPIO_MODE_IN_PU_NO_IT);                // TLAC INT (PA5)
    display.init_seg(GPIOB);                                       // inicializace segmentů
    display.init_dgt(GPIOG, PIN_4 | PIN_5 | PIN_6 | PIN_7);        // incializace digitů
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, 250);
    TIM4_Cmd(ENABLE);
    uint32_t cas = 0;
    while (1)
    {
        if (status == TRUE)
        {
        }
        for (uint64_t i = 0; i < 9999; i++)
        {
            cas += 1;
            delay.ms(100);
            display.num(cas, 4);
        }

        /* if (milis.get() - mtime_key > 55)
        {
            if (laser_read == RESET)
            {
                status = TRUE;
                printf("laser prerusen\n");
            }
            else
            {
                if (button1_read == RESET) // setování časomíry
                {
                    status = TRUE;
                }
                else if (button2_read == RESET) // reset časomíry
                {
                    status = FALSE;

                    nulovani();
                    buzzer(FALSE);
                    // display.show(0000, 4, 5);         // reset displeje
                }
                else
                {
                    status = FALSE;
                }
            }
        }
        else
        {
            // časomíra odstartována
            if (status == TRUE)
            {
                char szTemp[4];
                sec++;
                if (sec == 60)
                {
                    min++;
                    if (min == 99)
                    {
                        buzzer(TRUE);
                    }
                    sprintf(szTemp, "%d:%d", min, sec);
                    display.min(min, 2);
                    display.sec(sec, 2);
                }
                delay.us(1000);
            }
            else
            {
                buzzer(TRUE);
            }
        }
 */    }
}
