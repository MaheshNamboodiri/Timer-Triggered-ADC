#include "stm32f4xx.h"
#include "stdio.h"
extern void initialise_monitor_handles(void);


unsigned int value;
float stepSize=0.01171875;
float voltage;
int x=0;
void TIM2_Configuration(void){
    // enable TIM2 clock (bit0)
    RCC->APB1ENR |= (1 << 0);


    TIM2->PSC = 2000-1;
    TIM2->ARR = 1; //

     /* Reset the MMS Bits */
  TIM2->CR2 &= (uint16_t)~TIM_CR2_MMS;
  /* Select the TRGO source */
  TIM2->CR2 |=  TIM_CR2_MMS_1; //UPDATE EVENT


    // Enable Timer 2 module (CEN, bit0)
    TIM2->CR1 |= (1 << 0);


}

void init_ADC(void)
{
    RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;  //GPIOC clock enable
    GPIOC->MODER|=(3u<<(2*0));  //ADC input pin is analog mode, PC0
    RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;       //ADC clock enable
    RCC->CFGR |= 7<<13; //APB2ENR has 16/16 = 1Mhz
    ADC->CCR|=(3<<16); //1MHz/8 = 125kHz.

    ADC1->SQR1&=~ADC_SQR1_L;                        //set number of conversions per sequence to 1
    ADC1->SQR3&=~ADC_SQR3_SQ1;                  //clear channel select bits
    ADC1->SQR3|=10;                     //set channel
    ADC1->CR1 &= ~ADC_CR1_SCAN; //SCAN mode disabled
    ADC1->CR1 |=1<<25; //set 8 bit
    ADC1->CR2 &= ~ADC_CR2_CONT; //continuous conversion

    ADC1->CR2 &=  ~(1<<29);
    ADC1->CR2 |= (1<<28);   //Trigger on Rising edge

    //External Event TIM2 TRGO
    ADC1->CR2 |= 1<<25 | 1<<26;


    // ADC1->SMPR2 |= 7<<0; //488 cycles
    // //Sampling frequency = 125k/(480+8) = 256.147Hz
    // //For 50 Hz sine wave.



    ADC1->CR2|=ADC_CR2_ADON;                        //enable ADC
    ADC1->CR2|=ADC_CR2_SWSTART;
}

void msDelay(int msTime)
{
//Assume for loop take 12 clock cycles and system clock is 16MHz
int Time=msTime*1333;
    for(int i=0;i<Time;i++);

}

int main(){
    //FPU enable
    //Co-processor (core peripheral) access control register
    SCB->CPACR|=(0xF<<20);
    TIM2_Configuration();
    init_ADC();
    msDelay(500);
    x++;
    initialise_monitor_handles();
    while(1)
        {

        while (!(ADC1->SR & (1<<1))){
                    __NOP();

                }

                    value = ADC1->DR;
                    voltage = stepSize*value;


    }
}
