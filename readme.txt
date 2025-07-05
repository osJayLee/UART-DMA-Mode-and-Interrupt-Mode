定义DMA接受数据
static uint8_t rxBuffer[4096];  // DMA接收缓冲区
static volatile uint8_t rxFlag = 0;  // 接收完成标志
static uint16_t rxLength = 0;  // 实际接收数据长度


mian 中串口DMA初始化之后。
1.先开启DMA接收 	
HAL_UART_Receive_DMA(&huart1, rxBuffer, sizeof(rxBuffer));
2.开启串口空闲中断  用于接收完成之后再发送数据 
__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); 



中断函数实现
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




