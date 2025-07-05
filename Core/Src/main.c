/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// 在main.h中定义宏，切换接收模式
#define USE_DMA_RECEIVE  1  // 1=DMA模式，0=中断模式

#if USE_DMA_RECEIVE
    #define RECEIVE_MODE_DMA
#else
    #define RECEIVE_MODE_INTERRUPT
#endif
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit (&huart2 ,(uint8_t *)&ch,1,HAL_MAX_DELAY );
	return ch;
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef RECEIVE_MODE_DMA
static uint8_t rxBuffer[4096];  // DMA接收缓冲区
static volatile uint8_t rxFlag = 0;  // 接收完成标志
static uint16_t rxLength = 0;  // 实际接收数据长度

void Start_DMA_Receive(void) {
    HAL_UART_Receive_DMA(&huart1, rxBuffer, sizeof(rxBuffer));
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);  // 启用空闲中断[5](@ref)
}

void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	 if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET) {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);  // 清除空闲中断标志
        HAL_UART_DMAStop(&huart1);  // 停止DMA
        rxLength = sizeof(rxBuffer) - __HAL_DMA_GET_COUNTER(huart1.hdmarx);  // 计算接收长度
       // rxFlag = 1;  // 设置标志位
		    HAL_UART_Transmit_DMA(&huart1, rxBuffer, rxLength);
        HAL_UART_Receive_DMA(&huart1, rxBuffer, sizeof(rxBuffer));  // 重启DMA
    }
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}
#endif

#ifdef RECEIVE_MODE_INTERRUPT
uint8_t rxBuffer[4096];  // 接收缓冲区
volatile uint16_t rxIndex = 0;  // 接收索引
volatile uint8_t rxFlag = 0;    // 接收完成标志

void Start_Interrupt_Receive(void) {
HAL_UART_Receive_IT(&huart1, &rxBuffer[rxIndex], 1);
__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);  // 使能空闲中断
}

// 接收完成回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
   if(huart->Instance == USART1)
    {
        rxIndex++;
        if(rxIndex < 2048)
        {
            HAL_UART_Receive_IT(&huart1, &rxBuffer[rxIndex], 1);
        }
        else
        {
            rxIndex = 0;  // 缓冲区满，从头开始
            HAL_UART_Receive_IT(&huart1, &rxBuffer[rxIndex], 1);
        }
    }
}
void USART1_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */
    // 处理空闲中断
    if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);  // 清除空闲中断标志
        rxFlag = 1;  // 设置接收完成标志
    }
    /* USER CODE END USART1_IRQn 0 */
    
    HAL_UART_IRQHandler(&huart1);
    
    /* USER CODE BEGIN USART1_IRQn 1 */
    /* USER CODE END USART1_IRQn 1 */
}
#endif
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	#ifdef RECEIVE_MODE_DMA
	Start_DMA_Receive();
	#else
	Start_Interrupt_Receive();
	#endif
	static uint32_t count;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		#ifdef RECEIVE_MODE_DMA
		if (rxFlag) {
    rxFlag = 0;
   // HAL_UART_Transmit(&huart1, rxBuffer, rxLength, HAL_MAX_DELAY);  // 通过串口打印接收数据
		}  
	  #endif
	
		#ifdef RECEIVE_MODE_INTERRUPT
		 if(rxFlag)
			{
						rxFlag = 0;
						// 发送接收到的数据
						HAL_UART_Transmit(&huart1, rxBuffer, rxIndex, HAL_MAX_DELAY);
						rxIndex = 0;  // 重置索引
						HAL_UART_Receive_IT(&huart1, &rxBuffer[rxIndex], 1);  // 重新开始接收
			}
		#endif
		printf("count:%d",++count);
		HAL_Delay(50);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
