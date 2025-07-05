SET PATH=H:\Keil_v5\ARM\ARMCC\Bin;D:\Program Files (x86)\VMware\VMware Workstation\bin\;C:\Program Files\Microsoft MPI\Bin\;C:\Program Files\Common Files\Siemens\Automation\Simatic OAM\bin;C:\Program Files\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\Microsoft SQL Server\160\Tools\Binn\;C:\Program Files\Microsoft SQL Server\160\Tools\Binn\;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\170\Tools\Binn\;C:\Program Files\Microsoft SQL Server\160\DTS\Binn\;C:\Program Files (x86)\Microsoft SQL Server\160\DTS\Binn\;H:\Program Files (x86)\Dev-Cpp\MinGW64\bin;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;D:\Program Files\Git\cmd;H:\Program Files\nodejs\;C:\ProgramData\chocolatey\bin;D:\Program Files (x86)\NetSarang\Xshell 7\;C:\Program Files\dotnet\;C:\Program Files\CMake\bin;C:\Users\Administrator\AppData\Local\Programs\Python\Python39\Scripts\;C:\Users\Administrator\AppData\Local\Programs\Python\Python39\;C:\Users\Administrator\AppData\Local\Microsoft\WindowsApps;D:\Program Files (x86)\Atmel\Flip 3.4.7\bin;C:\Program Files\Azure Data Studio\bin;C:\Windows\System32;C:\Windows;C:\Windows\System32\Wbem;D:\Users\Administrator\AppData\Local\Programs\Microsoft VS Code\bin;C:\Users\Administrator\AppData\Roaming\npm;H:\Program Files\nodejs;
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=uart_dma&interrupt
SET CPU_CLOCK=0x007A1200
"H:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\uart_dma&interrupt\startup_stm32f103xb._ia"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\main.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\gpio.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\dma.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\usart.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_it.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_msp.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_gpio_ex.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_tim.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_tim_ex.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_uart.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_rcc.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_rcc_ex.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_gpio.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_dma.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_cortex.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_pwr.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_flash.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_flash_ex.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\stm32f1xx_hal_exti.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\uart_dma&interrupt\system_stm32f1xx.__i"
"H:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\uart_dma&interrupt\uart_dma&interrupt.lnp"
"H:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\uart_dma&interrupt\uart_dma&interrupt.axf" --i32combined --output ".\uart_dma&interrupt\uart_dma&interrupt.hex"
