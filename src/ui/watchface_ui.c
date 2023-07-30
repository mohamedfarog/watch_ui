
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <hal/nrf_gpio.h>
#include "watchface_ui.h"
#include <date_time.h>
#include<time.h>



void watchface_init(bool blstatus)
{
	char *bl_status;
     // set position
	 if (IS_ENABLED(CONFIG_LV_Z_POINTER_KSCAN)) {
	static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_letter_space(&style, 4);
    lv_style_set_text_line_space(&style, 18);
	static lv_style_t style1;
    lv_style_init(&style1);
	static lv_style_t bstyle;
lv_style_init(&bstyle);
	  lv_style_set_text_letter_space(&bstyle, 2);
	  lv_style_set_text_line_space(&bstyle, 14);
	  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_OPA_TRANSP);

	// lv_label_set_text(hello_world_label1, bl_status);
	   lv_obj_t* bluetooth_label = lv_label_create(lv_scr_act());
	   lv_obj_add_style(bluetooth_label, &bstyle, 0);
	   lv_style_set_text_font(&bstyle,  &lv_font_montserrat_20); 
	if (blstatus==1){
		lv_obj_set_style_text_color(bluetooth_label, lv_color_hex(0xe69138), LV_PART_MAIN);
		lv_obj_align(bluetooth_label, LV_ALIGN_TOP_MID, 0, 30);
		lv_label_set_text(bluetooth_label, LV_SYMBOL_BLUETOOTH);
	
		}
	else{
		lv_obj_set_style_text_color(bluetooth_label, lv_color_hex(0xffffff), LV_PART_MAIN);
		//lv_label_set_text(hello_world_label1, bl_status);
		lv_obj_align(bluetooth_label, LV_ALIGN_TOP_MID, 0, 30);
		lv_label_set_text(bluetooth_label, LV_SYMBOL_BLUETOOTH);

	}
		lv_obj_t * mywatch = lv_label_create(lv_scr_act());
	lv_obj_add_style(mywatch, &style, 0);
	lv_style_set_text_font(&style,  &lv_font_montserrat_28);
	lv_obj_set_style_text_color(mywatch, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_label_set_text(mywatch, "00:00:27");
    lv_obj_center(mywatch);

	lv_obj_t * date_label = lv_label_create(lv_scr_act());
	lv_obj_add_style(date_label, &style1, 0);
	lv_style_set_text_font(&style1,  &lv_font_montserrat_18);
	lv_obj_align(date_label, LV_ALIGN_BOTTOM_MID, 0, -35);
	lv_obj_set_style_text_color(date_label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_label_set_text(date_label, "TUESDAY\nJUL 23 2023");
	

	lv_task_handler();

	//}
	// while (1) {
	// 	if ((count % 100) == 0U) {
	// 		sprintf(count_str, "%d", count/100U);
	// 		lv_label_set_text(count_label, count_str);
	// 	}
	// 	lv_task_handler();
	// 	++count;
		// k_sleep(K_MSEC(1000));
	}
}


 void bluetooth_status(bool blstatus){
   
	char message1[] = "BL Connected!"; 
	char message2[] = "BL Not Connected!"; 

	// if(blstatus ==1){
	// 	show_notification(message1);
	// }
	// else{
	// 	show_notification(message2);
	// }
	 watchface_init(blstatus);
	
	}


