// /********************************************************************************
// * @file    tft.c
// * @author  Nam Tran
// * @version 2.0
// * @date    19/04/2022
// * @brief   tft driver to interface between lvgl and mbed stm bsp drivers
// *********************************************************************************
// * @details 
// * ----------------------------
// * Definitions and declarations
// * 
// * ----------------------------
// * Functions*
// * 
// *********************************************************************************
// */
 
// /* -------------------------------------------------------------------------- */
// /*                                   INCLUDES                                 */
// /* -------------------------------------------------------------------------- */
// #include "tft.h"
// #include "lvgl.h"
// #include "stm32f4xx.h"
// #include "bsp_drivers/stm32469i_discovery.h"
// #include "bsp_drivers/stm32469i_discovery_lcd.h"
// #include "bsp_drivers/stm32469i_discovery_sdram.h"
// /* -------------------------------------------------------------------------- */
// /*                                   DEFINES                                  */
// /* -------------------------------------------------------------------------- */
// #define LED4  DISCO_LED4
// /* -------------------------------------------------------------------------- */
// /*                                  PROTOTYPE                                 */
// /* -------------------------------------------------------------------------- */
// void tft_flush();
// /* -------------------------------------------------------------------------- */
// /*                                  FUNCTIONS                                 */
// /* -------------------------------------------------------------------------- */
// void tft_init() 
// {
//     BSP_LCD_Init();
//     BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
//     BSP_LCD_DisplayOn();
//     BSP_LCD_SelectLayer(0);
//     BSP_LCD_Clear(LCD_COLOR_BLACK);
//     BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
//     BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
//     BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

//     /*A static or global variable to store the buffers*/
//     static lv_disp_draw_buf_t disp_buf;

//     /*Static or global buffer(s)*/
//     static lv_color_t buf[LV_HOR_RES_MAX * 10];
    
//     /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
//     lv_disp_draw_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX*10);
    
//     static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/

//     lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
//     disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
//     //disp_drv.flush_cb = tft_flush_cb;        /*Set a flush callback to draw to the display*/
//     disp_drv.hor_res = LV_HOR_RES;                 /*Set the horizontal resolution in pixels*/
//     disp_drv.ver_res = LV_VER_RES;                 /*Set the vertical resolution in pixels*/

//     lv_area_t area;
// 	lv_color_t c = lv_color_hex(0xFF00FF00);

//     area.x1 = 0;
// 	area.y1 = 0;
// 	area.x2 = 300;
// 	area.y2 = 400;
//     tft_flush(&disp_drv,&area, &c);

//     lv_disp_t * disp;
//     disp = lv_disp_drv_register(&disp_drv); 
// }

// void tft_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
// {
//     /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one
//      *`put_px` is just an example, it needs to implemented by you.*/
//     int32_t x, y;
//     lv_color_t c = *color_p;
//     for(y = area->y1; y <= area->y2; y++) {
//         for(x = area->x1; x <= area->x2; x++) {
//             BSP_LCD_DrawPixel(x,y,c.full);
//             color_p++;
//         }
//     }

//     /* IMPORTANT!!!
//      * Inform the graphics library that you are ready with the flushing*/
//     lv_disp_flush_ready(disp_drv);
// }

// //////////////////////////////////////////////////////////////////
// // #define SDRAM_BANK_ADDR			SDRAM_DEVICE_ADDR 		/* Set in stm32469i_discovery_sdram.h (0xC0000000) */

// // #define DMA_STREAM DMA2_Stream0
// // #define DMA_CHANNEL DMA_CHANNEL_0
// // #define DMA_STREAM_IRQ DMA2_Stream0_IRQn
// // #define DMA_STREAM_IRQHANDLER DMA2_Stream0_IRQHandler

// // /**********************
// //  *      TYPEDEFS
// //  **********************/

// // /**********************
// //  *  STATIC PROTOTYPES
// //  **********************/

// // static void tft_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p);

// // /**********************
// //  *  STATIC VARIABLES
// //  **********************/
// // extern LTDC_HandleTypeDef  hltdc_eval;

// // #if TFT_USE_GPU != 0
// // static DMA2D_HandleTypeDef Dma2dHandle;
// // #endif

// // #if TFT_EXT_FB != 0
// // static __IO uint16_t *my_fb = (__IO uint16_t *)(SDRAM_BANK_ADDR);
// // #else
// // static uint16_t my_fb[TFT_HOR_RES * TFT_VER_RES];
// // #endif

// // /*DMA to flush to frame buffer*/
// // static void DMA_Config(void);
// // static void DMA_TransferComplete(DMA_HandleTypeDef *han);
// // static void DMA_TransferError(DMA_HandleTypeDef *han);

// // DMA_HandleTypeDef DmaHandle;
// // static lv_disp_drv_t disp_drv;
// // static int32_t x1_flush;
// // static int32_t y1_flush;
// // static int32_t x2_flush;
// // static int32_t y2_fill;
// // static int32_t y_fill_act;
// // static const lv_color_t *buf_to_flush;

// // /**********************
// //  *      MACROS
// //  **********************/

// // /**********************
// //  *   GLOBAL FUNCTIONS
// //  **********************/
// // /**
// //  * Initialize your display here
// //  */
// // void tft_init(void)
// // {
// //   static lv_color_t disp_buf1[TFT_HOR_RES * 40];
// //   static lv_disp_draw_buf_t buf;
// //   lv_disp_draw_buf_init(&buf, disp_buf1, NULL, TFT_HOR_RES * 40);

// //   lv_disp_drv_init(&disp_drv);

// //   BSP_LCD_Init();
// //   BSP_LCD_LayerDefaultInit(0, (uint32_t)my_fb);
// //   HAL_LTDC_SetPixelFormat(&hltdc_eval, LTDC_PIXEL_FORMAT_RGB565, 0);
// //   DMA_Config();
// //   disp_drv.draw_buf = &buf;
// //   disp_drv.flush_cb = tft_flush;
// //   disp_drv.hor_res = TFT_HOR_RES;
// //   disp_drv.ver_res = TFT_VER_RES;
// // #if TFT_USE_GPU != 0
// //   DMA2D_Config();
// //   disp_drv.gpu_blend_cb = gpu_mem_blend;
// //   disp_drv.gpu_fill_cb = gpu_mem_fill;
// // #endif
// //   lv_disp_drv_register(&disp_drv);
// // }

// // /**********************
// //  *   STATIC FUNCTIONS
// //  **********************/

// // /**
// //  * Flush a color buffer
// //  * @param x1 left coordinate of the rectangle
// //  * @param x2 right coordinate of the rectangle
// //  * @param y1 top coordinate of the rectangle
// //  * @param y2 bottom coordinate of the rectangle
// //  * @param color_p pointer to an array of colors
// //  */
// // static void tft_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
// // {
// //   /*Return if the area is out the screen*/
// //   if (area->x2 < 0)
// //     return;
// //   if (area->y2 < 0)
// //     return;
// //   if (area->x1 > TFT_HOR_RES - 1)
// //     return;
// //   if (area->y1 > TFT_VER_RES - 1)
// //     return;

// //   /*Truncate the area to the screen*/
// //   int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
// //   int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
// //   int32_t act_x2 = area->x2 > TFT_HOR_RES - 1 ? TFT_HOR_RES - 1 : area->x2;
// //   int32_t act_y2 = area->y2 > TFT_VER_RES - 1 ? TFT_VER_RES - 1 : area->y2;

// //   x1_flush = act_x1;
// //   y1_flush = act_y1;
// //   x2_flush = act_x2;
// //   y2_fill = act_y2;
// //   y_fill_act = act_y1;
// //   buf_to_flush = color_p;

// //   /*##-7- Start the DMA transfer using the interrupt mode #*/
// //   /* Configure the source, destination and buffer size DMA fields and Start DMA Stream transfer */
// //   /* Enable All the DMA interrupts */
// //   HAL_StatusTypeDef err;
// //   err = HAL_DMA_Start_IT(&DmaHandle, (uint32_t)buf_to_flush, (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],
// //                          (x2_flush - x1_flush + 1));
// //   if (err != HAL_OK)
// //   {
// //     while (1)
// //       ; /*Halt on error*/
// //   }
// // }

// // static void DMA_Config(void)
// // {
// //   /*## -1- Enable DMA2 clock #################################################*/
// //   __HAL_RCC_DMA2_CLK_ENABLE();

// //   /*##-2- Select the DMA functional Parameters ###############################*/
// //   DmaHandle.Init.Channel = DMA_CHANNEL;                           /* DMA_CHANNEL_0                    */
// //   DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;                /* M2M transfer mode                */
// //   DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;                     /* Peripheral increment mode Enable */
// //   DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                        /* Memory increment mode Enable     */
// //   DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;   /* Peripheral data alignment : 16bit */
// //   DmaHandle.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;      /* memory data alignment : 16bit     */
// //   DmaHandle.Init.Mode = DMA_NORMAL;                               /* Normal DMA mode                  */
// //   DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;                    /* priority level : high            */
// //   DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;                  /* FIFO mode enabled                */
// //   DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL; /* FIFO threshold: 1/4 full   */
// //   DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;                    /* Memory burst                     */
// //   DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;                 /* Peripheral burst                 */

// //   /*##-3- Select the DMA instance to be used for the transfer : DMA2_Stream0 #*/
// //   DmaHandle.Instance = DMA_STREAM;

// //   /*##-4- Initialize the DMA stream ##########################################*/
// //   if (HAL_DMA_Init(&DmaHandle) != HAL_OK)
// //   {
// //     while (1)
// //       ;
// //   }

// //   /*##-5- Select Callbacks functions called after Transfer complete and Transfer error */
// //   HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, DMA_TransferComplete);
// //   HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_ERROR_CB_ID, DMA_TransferError);

// //   /*##-6- Configure NVIC for DMA transfer complete/error interrupts ##########*/
// //   HAL_NVIC_SetPriority(DMA_STREAM_IRQ, 0, 0);
// //   HAL_NVIC_EnableIRQ(DMA_STREAM_IRQ);
// // }

// // /**
// //   * @brief  DMA conversion complete callback
// //   * @note   This function is executed when the transfer complete interrupt
// //   *         is generated
// //   * @retval None
// //   */
// // static void DMA_TransferComplete(DMA_HandleTypeDef *han)
// // {
// //   y_fill_act++;

// //   if (y_fill_act > y2_fill)
// //   {
// //     lv_disp_flush_ready(&disp_drv);
// //   }
// //   else
// //   {
// //     buf_to_flush += x2_flush - x1_flush + 1;
// //     /*##-7- Start the DMA transfer using the interrupt mode ####################*/
// //     /* Configure the source, destination and buffer size DMA fields and Start DMA Stream transfer */
// //     /* Enable All the DMA interrupts */
// //     if (HAL_DMA_Start_IT(han, (uint32_t)buf_to_flush, (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],
// //                          (x2_flush - x1_flush + 1)) != HAL_OK)
// //     {
// //       while (1)
// //         ; /*Halt on error*/
// //     }
// //   }
// // }

// // /**
// //   * @brief  DMA conversion error callback
// //   * @note   This function is executed when the transfer error interrupt
// //   *         is generated during DMA transfer
// //   * @retval None
// //   */
// // static void DMA_TransferError(DMA_HandleTypeDef *han)
// // {
// // }

// // /**
// //   * @brief  This function handles DMA Stream interrupt request.
// //   * @param  None
// //   * @retval None
// //   */
// // void DMA_STREAM_IRQHANDLER(void)
// // {
// //   /* Check the interrupt and clear flag */
// //   HAL_DMA_IRQHandler(&DmaHandle);
// // }