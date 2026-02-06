/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/services/bas.h>
#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/hid_indicators_changed.h>
#include <fonts.h>
#include "hid_indicators.h"
#include <zmk/events/caps_word_state_changed.h>
#include <lvgl.h>
#include "../theme.h"

// Offsets for each of the lock states.
#define LED_NLCK 0x01
#define LED_CLCK 0x02
#define LED_SLCK 0x04

// This defines the LOCK and UNLOCK icons found in the icons_lvgl.c font.
#define LOCK "\xEF\x80\xA3"
#define UNLOCK "\xEF\x8F\x81"

struct hid_indicators_state {
    uint8_t hid_indicators;     // hardware locks (CAPS/NUM/SCROLL)
    bool caps_word_active;      // ZMK caps_word state
};

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

static void set_hid_indicators(struct zmk_widget_hid_indicators *widget, struct hid_indicators_state state) {
    bool caps = state.hid_indicators & LED_CLCK;
    bool num = state.hid_indicators & LED_NLCK;
    bool scroll = state.hid_indicators & LED_SLCK;
    bool caps_word = state.caps_word_active;

    // Set the color based on active or inavtive.
    lv_color_t caps_color = caps ? THEME_COLOR_CAPS_ACTIVE : THEME_COLOR_LOCK_INACTIVE;
    lv_color_t num_color = num ? THEME_COLOR_NUM_ACTIVE : THEME_COLOR_LOCK_INACTIVE;
    lv_color_t scroll_color = scroll ? THEME_COLOR_SCROLL_ACTIVE : THEME_COLOR_LOCK_INACTIVE;
    lv_color_t caps_word_color = caps_word ? THEME_COLOR_CAPS_WORD_ACTIVE : THEME_COLOR_LOCK_INACTIVE;

    // Set the icon based on locked or unlocked.
    const char* cap_icon_choice = caps ? LOCK : UNLOCK;
    const char* num_icon_choice = num ? LOCK : UNLOCK;
    const char* scr_icon_choice = scroll ? LOCK : UNLOCK;
    const char* caps_word_icon_choice = caps_word ? LOCK : UNLOCK;  // NEW!

    // Set label colors and text
    lv_obj_set_style_text_font(widget->caps_icon, &icons_lvgl, 0);
    lv_obj_set_style_text_color(widget->caps_icon, caps_color, 0);
    lv_label_set_text(widget->caps_icon, cap_icon_choice);
    
    lv_obj_set_style_text_color(widget->caps_label, caps_color, 0);
    lv_label_set_text(widget->caps_label, "CAP");

    lv_obj_set_style_text_font(widget->num_icon, &icons_lvgl, 0);
    lv_obj_set_style_text_color(widget->num_icon, num_color, 0);
    lv_label_set_text(widget->num_icon, num_icon_choice);
    
    lv_label_set_text(widget->num_label, "NUM");
    lv_obj_set_style_text_color(widget->num_label, num_color, 0);

    lv_obj_set_style_text_font(widget->scroll_icon, &icons_lvgl, 0);
    lv_obj_set_style_text_color(widget->scroll_icon, scroll_color, 0);
    lv_label_set_text(widget->scroll_icon, scr_icon_choice);

    lv_label_set_text(widget->scroll_label, "SCR");
    lv_obj_set_style_text_color(widget->scroll_label, scroll_color, 0);

    lv_obj_set_style_text_font(widget->caps_word_icon, &icons_lvgl, 0);
    lv_obj_set_style_text_color(widget->caps_word_icon, caps_word_color, 0);
    lv_label_set_text(widget->caps_word_icon, caps_word_icon_choice);
    
    lv_obj_set_style_text_color(widget->caps_word_label, caps_word_color, 0);
    lv_label_set_text(widget->caps_word_label, "WRD");

}

void hid_indicators_update_cb(struct hid_indicators_state state) {
    struct zmk_widget_hid_indicators *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
        set_hid_indicators(widget, state);
    }
}

static struct hid_indicators_state hid_indicators_get_state(const zmk_event_t *eh) {
    struct zmk_hid_indicators_changed *ev = as_zmk_hid_indicators_changed(eh);
    return (struct hid_indicators_state){
        .hid_indicators = ev->indicators,
        .caps_word_active = false,  // not used for HID events
    };
}

// NEW: Handle caps_word state changes
static struct hid_indicators_state caps_word_get_state(const zmk_event_t *eh) {
    struct zmk_caps_word_state_changed *ev = as_zmk_caps_word_state_changed(eh);
    return (struct hid_indicators_state){
        .hid_indicators = 0,  // not used for caps_word events
        .caps_word_active = ev->active,
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_hid_indicators, struct hid_indicators_state,
                            hid_indicators_update_cb, hid_indicators_get_state)

ZMK_DISPLAY_WIDGET_LISTENER(widget_caps_word_indicators, struct hid_indicators_state,
                            hid_indicators_update_cb, caps_word_get_state)

ZMK_SUBSCRIPTION(widget_hid_indicators, zmk_hid_indicators_changed);
ZMK_SUBSCRIPTION(widget_caps_word_indicators, zmk_caps_word_state_changed);

int zmk_widget_hid_indicators_init(struct zmk_widget_hid_indicators *widget, lv_obj_t *parent) {
    // Create the Main Container
    widget->cont = lv_obj_create(parent);
    lv_obj_set_size(widget->cont, 80, 105);
    lv_obj_set_style_border_width(widget->cont, 0, 0);
    lv_obj_set_style_pad_all(widget->cont, 0, 0);
    lv_obj_set_style_bg_opa(widget->cont, LV_OPA_TRANSP, 0);
    lv_obj_set_style_text_font(widget->cont, &lv_font_montserrat_20, 0);

    // Setup the CAPS Lock Icon and Label
    widget->caps_label = lv_label_create(widget->cont);
    widget->caps_icon = lv_label_create(widget->cont);
    lv_obj_align(widget->caps_icon, LV_ALIGN_TOP_LEFT, 60, 0);
    lv_obj_align(widget->caps_label, LV_ALIGN_TOP_LEFT, 0, 3);
    
    // Setup the CAPS_WORD Icon and Label
    widget->caps_word_label = lv_label_create(widget->cont);
    widget->caps_word_icon = lv_label_create(widget->cont);
    lv_obj_align(widget->caps_word_icon, LV_ALIGN_TOP_LEFT, 60, 25);
    lv_obj_align(widget->caps_word_label, LV_ALIGN_TOP_LEFT, 0, 28);

    // Setup the NUM Lock Icon and Label
    widget->num_label = lv_label_create(widget->cont);
    widget->num_icon = lv_label_create(widget->cont);
    lv_obj_align(widget->num_icon, LV_ALIGN_TOP_LEFT, 60, 50);
    lv_obj_align(widget->num_label, LV_ALIGN_TOP_LEFT, 0, 53);

    // Setup the SCROLL Lock Icon and Label
    widget->scroll_label = lv_label_create(widget->cont);
    widget->scroll_icon = lv_label_create(widget->cont);
    lv_obj_align(widget->scroll_icon, LV_ALIGN_TOP_LEFT, 60, 75);
    lv_obj_align(widget->scroll_label, LV_ALIGN_TOP_LEFT, 0, 78);

    sys_slist_append(&widgets, &widget->node);

    widget_hid_indicators_init();

    // Initialize with all inactive
    struct hid_indicators_state initial = {0};
    set_hid_indicators(widget, initial);

    return 0;
}

lv_obj_t *zmk_widget_hid_indicators_obj(struct zmk_widget_hid_indicators *widget) {
    return widget->cont;
}
