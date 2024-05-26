# RTX_RTOS_DAS
Data Acquisition System using the Keil RTX Real-Time OS.<br>
# About Project <br>
The project focuses on the implementation of various protocols such as UART, SPI, and I2C and A/D Converters to show various parameters of data collected from sensors onto a UART Terminal.
The data acquisition system is built using the ARM-7 Based LPC2129 Microcontroller. The data is acquired from the microcontroller's onboard sensors using ADC and also from off-board sensors using external ADC through SPI protocol, and shows the data every second including the time of data acquisition using a RTC interfaced through I2C protocol, and all the data is displayed in the PC monitor through UART Serial terminal.
The sensors used include the onboard temperature and potentiometer (used as a simulation for pressure) on the Rhydolabz LPC2129 Microcontroller development board, DS1307 RTC interfaced with I2C for printing the time of data acquisition, and the MCP3204 External ADC to connect LDR interfaced through SPI.<br>
# RTOS Implementation <br>
The real-time operating system used in the project  is the RTX RTOS which comes native with the Keil Vision 5. The Keil RTX is a royalty-free, deterministic Real-Time Operating System designed for ARM and Cortex-M devices. Here we have designed and implemented Cooperative Multitasking (defined in RTX_Config) to complete tasks so that they work cooperatively. <br>
When making your project be sure to go to Target Options and select Operating system as "RTX Kernel". Also, use the startup code provided in the repository or edit the startup file of your LPC Board as follows:
```
256. FIQ_Addr        DCD     FIQ_Handler
257.
258.  IMPORT SWI_Handler //add this line with tab space at line 258 of the startup code.
259. Undef_Handler   B       Undef_Handler
260. ;SWI_Handler     B       SWI_Handler //comment out this line using semicolon
261. PAbt_Handler    B       PAbt_Handler
```
The Proteus file and Keil file required to simulate the project are also available in the repository.
