/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "i2c.h"
#include "app_lorawan.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define RX_SIZE					2U
#define I2C_SEND_INTERVAL_US	500000U
uint32_t count = 0U;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

void I2C1_EV_IRQHandler(void)
{
	HAL_I2C_EV_IRQHandler(&hi2c1);
}

void SPI1_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&hspi1);
}

void I2C1_ER_IRQHandler(void)
{
	HAL_I2C_ER_IRQHandler(&hi2c1);
}

void I2C2_EV_IRQHandler(void)
{
	HAL_I2C_EV_IRQHandler(&hi2c2);
}

void I2C2_ER_IRQHandler(void)
{
	HAL_I2C_ER_IRQHandler(&hi2c2);
}

void SPI2_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&hspi2);
}

void I2C3_EV_IRQHandler(void)
{
	HAL_I2C_EV_IRQHandler(&hi2c3);
}

void I2C3_ER_IRQHandler(void)
{
	HAL_I2C_ER_IRQHandler(&hi2c3);
}



uint32_t get_timer_2_count();

void hal_callback_i2c_controller_tx_complete(I2C_HandleTypeDef *hi2c);
void hal_callback_i2c_controller_rx_complete(I2C_HandleTypeDef *hi2c);
void hal_callback_i2c_peripheral_rx_complete(I2C_HandleTypeDef *hi2c);
void hal_callback_i2c_listen_complete(I2C_HandleTypeDef *hi2c);
void hal_callback_i2c_error(I2C_HandleTypeDef *hi2c);

void hal_callback_spi_controller_tx_rx_complete(SPI_HandleTypeDef *hspi);
void hal_callback_spi_controller_error(SPI_HandleTypeDef *hspi);

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t i2c_rx_data[RX_SIZE] = { 0x00, 0x00 };
uint8_t rx_bytes[RX_SIZE] = { 0x00, 0x00 };
uint8_t i2c_tx_data[5] = { 0x01, 0x05, 0x06, 0x0A, 0x01 };
uint8_t received = 1U;
uint8_t sent = 0U;
uint32_t timeout_count = 0U;
uint8_t spi_tx_data[5] = { 0x01, 0x05, 0x06, 0x0A, 0x01 };
uint8_t spi_rx_data[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
//  MX_LoRaWAN_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */



  /* USER CODE END 2 */

  /* Boot CPU2 */
  HAL_PWREx_ReleaseCore(PWR_CORE_CPU2);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_MASTER_TX_COMPLETE_CB_ID, hal_callback_i2c_controller_tx_complete);
	HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_MASTER_RX_COMPLETE_CB_ID, hal_callback_i2c_controller_rx_complete);
	HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_SLAVE_RX_COMPLETE_CB_ID, hal_callback_i2c_peripheral_rx_complete);
	HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_LISTEN_COMPLETE_CB_ID, hal_callback_i2c_listen_complete);


	HAL_SPI_RegisterCallback(&hspi2, HAL_SPI_TX_RX_COMPLETE_CB_ID, hal_callback_spi_controller_tx_rx_complete);
	HAL_SPI_RegisterCallback(&hspi2, HAL_SPI_ERROR_CB_ID, hal_callback_spi_controller_error);



	HAL_TIM_Base_Start(&htim2);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

	while (1)
	{
		//
		//	  i2c_rx_data[0] = 0x00;
		//	  i2c_rx_data[1] = 0x00;

		if (get_timer_2_count() - count > I2C_SEND_INTERVAL_US)
		{
			  HAL_I2C_Master_Transmit_IT(&hi2c1, (0x14 << 1), i2c_tx_data, 5);

	//	  			  count = get_timer_2_count();

			  count = get_timer_2_count();

//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
//			if (HAL_SPI_TransmitReceive_IT(&hspi2, spi_tx_data, spi_rx_data, 5) == HAL_OK)
//			{
//				count = get_timer_2_count();
//			}
		}

		if (sent == 1U)
		{
			HAL_I2C_Master_Receive_IT(&hi2c1, (0x14 << 1), i2c_rx_data, RX_SIZE);
			sent = 0U;
		}
	}
    /* USER CODE END WHILE */
//    MX_LoRaWAN_Process();

    /* USER CODE BEGIN 3 */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_PWR;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
  RCC_OscInitStruct.HSEDiv = RCC_HSE_DIV1;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
  HAL_RCCEx_EnableLSCO(RCC_LSCOSOURCE_LSI);
}

/* USER CODE BEGIN 4 */

uint32_t get_timer_2_count()
{
	return htim2.Instance->CNT;
}

void hal_callback_i2c_controller_tx_complete(I2C_HandleTypeDef *hi2c)
{
	sent = 1U;

//	timeout_count = 0U;
}

void hal_callback_i2c_controller_rx_complete(I2C_HandleTypeDef *hi2c)
{
//	for (uint8_t index = 0; 0 < RX_SIZE; ++index)
//	{
//		rx_bytes[index] = i2c_rx_data[index];
//	}
//	received = 1U;
}

void hal_callback_i2c_peripheral_rx_complete(I2C_HandleTypeDef *hi2c)
{

}

void hal_callback_i2c_listen_complete(I2C_HandleTypeDef *hi2c)
{
	for (uint8_t index = 0; 0 < RX_SIZE; ++index)
	{
		rx_bytes[index] = i2c_rx_data[index];
	}
}

void hal_callback_spi_controller_tx_rx_complete(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
}

void hal_callback_spi_controller_error(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
}


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
