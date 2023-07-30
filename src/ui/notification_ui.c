#include "notification_ui.h"
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>




void show_notification(char mystr[])
{
    	
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);
	 lv_obj_t *mbox1 = lv_msgbox_create(lv_scr_act(), "NOTIFICATION!", "Message", NULL, false);
	 lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_add_event_cb(mbox1, NULL, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(mbox1);
 


}

