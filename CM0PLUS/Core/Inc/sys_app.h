/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sys_app.h
  * @author  MCD Application Team
  * @brief   Function prototypes for sys_app.c file
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
#ifndef __SYS_APP_H__
#define __SYS_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "mbmux_table.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported defines ----------------------------------------------------------*/
/* currently not supported */
/* #define ALLOW_KMS_VIA_MBMUX */

/* USER CODE BEGIN ED */

/* USER CODE END ED */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN APP_PRINT */
/* Map your own trace mechanism or to map UTIL_ADV_TRACE see examples from CubeFw, e.g.: */
#define APP_PRINTF(...)     /* do{ {UTIL_ADV_TRACE_COND_FSend(VLEVEL_ALWAYS, T_REG_OFF, TS_OFF, __VA_ARGS__);} }while(0); */
#define APP_LOG(TS,VL,...)  /* do{ {UTIL_ADV_TRACE_COND_FSend(VL, T_REG_OFF, TS, __VA_ARGS__);} }while(0); */
/* USER CODE END APP_PRINT */

/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief initialize MBMUXIF System and send a notification to Cm4 when ready
  */
void SystemApp_Init(void);

/**
  * @brief  callback to get the board 64 bits unique ID
  * @param  id unique ID
  */
void GetUniqueId(uint8_t *id);

/**
  * @brief  callback to get the board 32 bits unique ID (LSB)
  * @param  devAddr Device Address
  */
void GetDevAddr(uint32_t *devAddr);

/**
  * @brief Returns sec and msec based on the systime in use
  * @param buff to update with timestamp
  * @param size of updated buffer
  */
void TimestampNow(uint8_t *buff, uint16_t *size);

/**
  * @brief  Process System Command
  * @param  ComObj exchange buffer parameter
  */
void Process_Sys_Cmd(MBMUX_ComParam_t *ComObj);
#ifdef ALLOW_KMS_VIA_MBMUX /* currently not supported */
/**
  * @brief  Process KMS Command
  * @param  ComObj exchange buffer parameter
  */
void Process_Kms_Cmd(MBMUX_ComParam_t *ComObj);
#endif /* ALLOW_KMS_VIA_MBMUX */

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __SYS_APP_H__ */
