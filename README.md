# Timer-Triggered-ADC

For Arm Cortex M core microcontroller, STM32F407, I have designed a Peripheral triggered ADC driver from scratch, using bare metal code in Embedded C. 
The development environment used was STM32CubeIDE. The idea behind this is to control sampling frequency using a timer peripheral, while leaving main CPU processor to perform more important tasks.
