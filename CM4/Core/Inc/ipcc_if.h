/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ipcc_if.h
  * @author  MCD Application Team
  * @brief   This file contains the interface of the ipcc driver on CM4.
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
#ifndef __IPCC_IF_CM4_H__
#define __IPCC_IF_CM4_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "ipcc.h"

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
  * @brief Initialize IPCC and register upper and downer callbacks
  * @param  IPCC_IF_ResponseRcv_cb     response callback
  * @param  IPCC_IF_NotificationRcv_cb notification callback
  */
void IPCC_IF_Init(void (*IPCC_IF_ResponseRcv_cb)(uint32_t channelIdx),
                  void (*IPCC_IF_NotificationRcv_cb)(uint32_t channelIdx));

/**
  * @brief Get Command status (abstract application from Ipcc handler and channel direction)
  * @param channelIdx  ipcc channel
  * @return ipcc channel status
  * @retval IPCC_CHANNEL_STATUS_FREE 0
  * @retval IPCC_CHANNEL_STATUS_OCCUPIED 1
  */
uint32_t IPCC_IF_CmdRespStatus(uint32_t channelIdx);

/**
  * @brief Get notification status (abstract application from Ipcc handler and channel direction)
  * @param channelIdx  ipcc channel
  * @return ipcc channel status
  * @retval IPCC_CHANNEL_STATUS_FREE 0
  * @retval IPCC_CHANNEL_STATUS_OCCUPIED 1
  */
uint32_t IPCC_IF_NotifAckStatus(uint32_t channelIdx);

/**
  * @brief Send Cmd to the remote CPU (abstract application from Ipcc handler and channel direction)
  * @param channelIdx  ipcc channel
  * @return ipcc status [OK: 0 , fail: -1]
  */
int32_t IPCC_IF_CommandSnd(uint32_t channelIdx);

/**
  * @brief Send Ack to the remote CPU (abstract application from Ipcc handler and channel direction)
  * @param channelIdx  ipcc channel
  * @return ipcc status [OK: 0 , fail: -1]
  */
int32_t IPCC_IF_AcknowledgeSnd(uint32_t channelIdx);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __IPCC_IF_CM4_H__ */
