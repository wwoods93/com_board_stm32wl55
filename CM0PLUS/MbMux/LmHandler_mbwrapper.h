/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    LmHandler_mbwrapper.h
  * @author  MCD Application Team
  * @brief   This file implements the CM0PLUS side wrapper of the LmHandler
  *          interface shared between M0 and M4.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LMHANDLER_MBWRAPPER_CM0PLUS_H__
#define __LMHANDLER_MBWRAPPER_CM0PLUS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mbmux_table.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  This function processes the LmHandler events callbacks from CM4
  * @param  ComObj exchange buffer parameter
  */
void Process_Lora_Cmd(MBMUX_ComParam_t *ComObj);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*__LMHANDLER_MBWRAPPER_CM0PLUS_H__ */
