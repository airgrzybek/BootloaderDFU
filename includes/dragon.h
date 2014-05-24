/*
 * dragon.h
 *
 *  Created on: 3 maj 2014
 *      Author: grzybek
 */

#ifndef DRAGON_H_
#define DRAGON_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32_eval_legacy.h"

typedef enum
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;

typedef enum
{
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY = 2,
  BUTTON_RIGHT = 3,
  BUTTON_LEFT = 4,
  BUTTON_UP = 5,
  BUTTON_DOWN = 6,
  BUTTON_SEL = 7
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum
{
  JOY_NONE = 0,
  JOY_SEL = 1,
  JOY_DOWN = 2,
  JOY_LEFT = 3,
  JOY_RIGHT = 4,
  JOY_UP = 5
} JOYState_TypeDef
;

typedef enum
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;

#if !defined (USE_DRAGON_BOARD)
 #define USE_DRAGON_BOARD
#endif


#define LEDn                             4

#define LED1_PIN                         GPIO_Pin_6
#define LED1_GPIO_PORT                   GPIOF
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOF

#define LED2_PIN                         GPIO_Pin_7
#define LED2_GPIO_PORT                   GPIOF
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOF

#define LED3_PIN                         GPIO_Pin_8
#define LED3_GPIO_PORT                   GPIOF
#define LED3_GPIO_CLK                    RCC_APB2Periph_GPIOF

#define LED4_PIN                         GPIO_Pin_9
#define LED4_GPIO_PORT                   GPIOF
#define LED4_GPIO_CLK                    RCC_APB2Periph_GPIOF


#define BUTTONn                          8

/**
 * @brief Wakeup push-button
 */
#define WAKEUP_BUTTON_PIN                GPIO_Pin_0
#define WAKEUP_BUTTON_GPIO_PORT          GPIOA
#define WAKEUP_BUTTON_GPIO_CLK           RCC_APB2Periph_GPIOA
#define WAKEUP_BUTTON_EXTI_LINE          EXTI_Line0
#define WAKEUP_BUTTON_EXTI_PORT_SOURCE   GPIO_PortSourceGPIOA
#define WAKEUP_BUTTON_EXTI_PIN_SOURCE    GPIO_PinSource0
#define WAKEUP_BUTTON_EXTI_IRQn          EXTI0_IRQn
/**
 * @brief Tamper push-button
 */
#define TAMPER_BUTTON_PIN                GPIO_Pin_13
#define TAMPER_BUTTON_GPIO_PORT          GPIOC
#define TAMPER_BUTTON_GPIO_CLK           RCC_APB2Periph_GPIOC
#define TAMPER_BUTTON_EXTI_LINE          EXTI_Line13
#define TAMPER_BUTTON_EXTI_PORT_SOURCE   GPIO_PortSourceGPIOC
#define TAMPER_BUTTON_EXTI_PIN_SOURCE    GPIO_PinSource13
#define TAMPER_BUTTON_EXTI_IRQn          EXTI15_10_IRQn
/**
 * @brief Key push-button
 */
#define KEY_BUTTON_PIN                   GPIO_Pin_8
#define KEY_BUTTON_GPIO_PORT             GPIOA
#define KEY_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOA
#define KEY_BUTTON_EXTI_LINE             EXTI_Line8
#define KEY_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOA
#define KEY_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource8
#define KEY_BUTTON_EXTI_IRQn             EXTI9_5_IRQn
/**
 * @brief Joystick Right push-button
 */
#define RIGHT_BUTTON_PIN                 GPIO_Pin_13
#define RIGHT_BUTTON_GPIO_PORT           GPIOG
#define RIGHT_BUTTON_GPIO_CLK            RCC_APB2Periph_GPIOG
#define RIGHT_BUTTON_EXTI_LINE           EXTI_Line13
#define RIGHT_BUTTON_EXTI_PORT_SOURCE    GPIO_PortSourceGPIOG
#define RIGHT_BUTTON_EXTI_PIN_SOURCE     GPIO_PinSource13
#define RIGHT_BUTTON_EXTI_IRQn           EXTI15_10_IRQn
/**
 * @brief Joystick Left push-button
 */
#define LEFT_BUTTON_PIN                  GPIO_Pin_14
#define LEFT_BUTTON_GPIO_PORT            GPIOG
#define LEFT_BUTTON_GPIO_CLK             RCC_APB2Periph_GPIOG
#define LEFT_BUTTON_EXTI_LINE            EXTI_Line14
#define LEFT_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOG
#define LEFT_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource14
#define LEFT_BUTTON_EXTI_IRQn            EXTI15_10_IRQn
/**
 * @brief Joystick Up push-button
 */
#define UP_BUTTON_PIN                    GPIO_Pin_15
#define UP_BUTTON_GPIO_PORT              GPIOG
#define UP_BUTTON_GPIO_CLK               RCC_APB2Periph_GPIOG
#define UP_BUTTON_EXTI_LINE              EXTI_Line15
#define UP_BUTTON_EXTI_PORT_SOURCE       GPIO_PortSourceGPIOG
#define UP_BUTTON_EXTI_PIN_SOURCE        GPIO_PinSource15
#define UP_BUTTON_EXTI_IRQn              EXTI15_10_IRQn
/**
 * @brief Joystick Down push-button
 */
#define DOWN_BUTTON_PIN                  GPIO_Pin_3
#define DOWN_BUTTON_GPIO_PORT            GPIOD
#define DOWN_BUTTON_GPIO_CLK             RCC_APB2Periph_GPIOD
#define DOWN_BUTTON_EXTI_LINE            EXTI_Line3
#define DOWN_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOD
#define DOWN_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource3
#define DOWN_BUTTON_EXTI_IRQn            EXTI3_IRQn
/**
 * @brief Joystick Sel push-button
 */
#define SEL_BUTTON_PIN                   GPIO_Pin_7
#define SEL_BUTTON_GPIO_PORT             GPIOG
#define SEL_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOG
#define SEL_BUTTON_EXTI_LINE             EXTI_Line7
#define SEL_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOG
#define SEL_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource7
#define SEL_BUTTON_EXTI_IRQn             EXTI9_5_IRQn

#define COMn                             2


#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCC_APB2Periph_USART1
#define EVAL_COM1_TX_PIN                 GPIO_Pin_9
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_RX_PIN                 GPIO_Pin_10
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_IRQn                   USART1_IRQn

#define EVAL_COM2                        USART2
#define EVAL_COM2_CLK                    RCC_APB1Periph_USART2
#define EVAL_COM2_TX_PIN                 GPIO_Pin_2
#define EVAL_COM2_TX_GPIO_PORT           GPIOA
#define EVAL_COM2_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM2_RX_PIN                 GPIO_Pin_3
#define EVAL_COM2_RX_GPIO_PORT           GPIOA
#define EVAL_COM2_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM2_IRQn                   USART2_IRQn

#define SD_DETECT_PIN                    GPIO_Pin_11                 /* PF.11 */
#define SD_DETECT_GPIO_PORT              GPIOF                       /* GPIOF */
#define SD_DETECT_GPIO_CLK               RCC_APB2Periph_GPIOF

#define SDIO_FIFO_ADDRESS                ((uint32_t)0x40018080)

#define SDIO_INIT_CLK_DIV                ((uint8_t)0xB2)

#define SDIO_TRANSFER_CLK_DIV            ((uint8_t)0x01)

#define SD_SDIO_DMA                      DMA2
#define SD_SDIO_DMA_CLK                  RCC_AHBPeriph_DMA2
#define SD_SDIO_DMA_CHANNEL              DMA2_Channel4
#define SD_SDIO_DMA_FLAG_TC              DMA2_FLAG_TC4
#define SD_SDIO_DMA_FLAG_TE              DMA2_FLAG_TE4
#define SD_SDIO_DMA_FLAG_HT              DMA2_FLAG_HT4
#define SD_SDIO_DMA_FLAG_GL              DMA2_FLAG_GL4
#define SD_SDIO_DMA_IRQn                 DMA2_Channel4_5_IRQn
#define SD_SDIO_DMA_IRQHANDLER           DMA2_Channel4_5_IRQHandler

#define sFLASH_SPI                       SPI1
#define sFLASH_SPI_CLK                   RCC_APB2Periph_SPI1
#define sFLASH_SPI_SCK_PIN               GPIO_Pin_5                  /* PA.05 */
#define sFLASH_SPI_SCK_GPIO_PORT         GPIOA                       /* GPIOA */
#define sFLASH_SPI_SCK_GPIO_CLK          RCC_APB2Periph_GPIOA
#define sFLASH_SPI_MISO_PIN              GPIO_Pin_6                  /* PA.06 */
#define sFLASH_SPI_MISO_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MISO_GPIO_CLK         RCC_APB2Periph_GPIOA
#define sFLASH_SPI_MOSI_PIN              GPIO_Pin_7                  /* PA.07 */
#define sFLASH_SPI_MOSI_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOA
#define sFLASH_CS_PIN                    GPIO_Pin_2                  /* PB.02 */
#define sFLASH_CS_GPIO_PORT              GPIOB                       /* GPIOB */
#define sFLASH_CS_GPIO_CLK               RCC_APB2Periph_GPIOB

#define LM75_I2C                         I2C1
#define LM75_I2C_CLK                     RCC_APB1Periph_I2C1
#define LM75_I2C_SCL_PIN                 GPIO_Pin_6                  /* PB.06 */
#define LM75_I2C_SCL_GPIO_PORT           GPIOB                       /* GPIOB */
#define LM75_I2C_SCL_GPIO_CLK            RCC_APB2Periph_GPIOB
#define LM75_I2C_SDA_PIN                 GPIO_Pin_7                  /* PB.07 */
#define LM75_I2C_SDA_GPIO_PORT           GPIOB                       /* GPIOB */
#define LM75_I2C_SDA_GPIO_CLK            RCC_APB2Periph_GPIOB
#define LM75_I2C_SMBUSALERT_PIN          GPIO_Pin_5                  /* PB.05 */
#define LM75_I2C_SMBUSALERT_GPIO_PORT    GPIOB                       /* GPIOB */
#define LM75_I2C_SMBUSALERT_GPIO_CLK     RCC_APB2Periph_GPIOB
#define LM75_I2C_DR                      ((uint32_t)0x40005410)

#define LM75_DMA_CLK                     RCC_AHBPeriph_DMA1
#define LM75_DMA_TX_CHANNEL              DMA1_Channel6
#define LM75_DMA_RX_CHANNEL              DMA1_Channel7
#define LM75_DMA_TX_TCFLAG               DMA1_FLAG_TC6
#define LM75_DMA_RX_TCFLAG               DMA1_FLAG_TC7

void STM_EVAL_LEDInit(Led_TypeDef Led);
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);
void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void sFLASH_LowLevel_DeInit(void);
void sFLASH_LowLevel_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* DRAGON_H_ */