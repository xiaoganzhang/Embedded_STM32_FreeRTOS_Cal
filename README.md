# Embedded_STM32_FreeRTOS_Cal
Based on FreeRTOS on STM32(STM32F103-mini). A simple Resistive touch screen calculator
Here I posted the most crucial function that I wrote, one is the layout, one is getting the return value from the touch screen, and one is the logic of the calculator. 

I created two threads, the first for the scan return of the touch screen and the second for the calculator logic. By touching a number or symbol to unhook the calculator logic task and let the calculator logic function execute at one time, the advantage of it is that the whole logic looks clearer and simpler.

It is a personal practice project, plus the layout was very simple, so I didn't use any GUI lib like STemwin, etc.
