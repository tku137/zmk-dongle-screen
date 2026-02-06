/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lvgl.h>

/**
 * YADS Theme System
 * 
 * Centralizes all colors used across widgets for easy theming.
 * Each theme defines colors for different widget states and elements.
 */

// Theme color definitions
struct yads_theme {
    // Battery widget colors
    lv_color_t battery_critical;      // <= 10%
    lv_color_t battery_low;            // <= 20%
    lv_color_t battery_medium;         // <= 30%
    lv_color_t battery_good;           // <= 90%
    lv_color_t battery_full;           // > 90%
    
    // HID Indicators colors
    lv_color_t caps_lock_active;
    lv_color_t num_lock_active;
    lv_color_t scroll_lock_active;
    lv_color_t caps_word_active;
    lv_color_t lock_inactive;
    
    // Output status colors
    lv_color_t usb_connected;
    lv_color_t usb_disconnected;
    lv_color_t ble_connected;
    lv_color_t ble_bonded;
    lv_color_t ble_inactive;
    
    // WPM widget colors
    lv_color_t wpm_gradient_start;
    lv_color_t wpm_gradient_end;
    lv_color_t wpm_border;
    
    // Layer widget colors
    lv_color_t layer_active;
    lv_color_t layer_inactive;
    lv_color_t layer_text;
    
    // Common colors
    lv_color_t background;
    lv_color_t text_primary;
    lv_color_t text_secondary;
    lv_color_t border;
    lv_color_t inactive;
};

// Theme selection based on Kconfig
#if IS_ENABLED(CONFIG_DONGLE_SCREEN_THEME_TOKYONIGHT)
    #define YADS_THEME_NAME "Tokyo Night"
    // Tokyo Night (Night variant) color palette
    // Use compound literals to create colors properly
    #define THEME_BATTERY_CRITICAL    ((lv_color_t)LV_COLOR_MAKE(0xF7, 0x76, 0x8E))
    #define THEME_BATTERY_LOW         ((lv_color_t)LV_COLOR_MAKE(0xFF, 0x9E, 0x64))
    #define THEME_BATTERY_MEDIUM      ((lv_color_t)LV_COLOR_MAKE(0xE0, 0xAF, 0x68))
    #define THEME_BATTERY_GOOD        ((lv_color_t)LV_COLOR_MAKE(0x9E, 0xCE, 0x6A))
    #define THEME_BATTERY_FULL        ((lv_color_t)LV_COLOR_MAKE(0x7D, 0xCF, 0xFF))
    
    #define THEME_CAPS_ACTIVE         ((lv_color_t)LV_COLOR_MAKE(0x9E, 0xCE, 0x6A))  // Green
    #define THEME_NUM_ACTIVE          ((lv_color_t)LV_COLOR_MAKE(0x7A, 0xA2, 0xF7))  // Blue
    #define THEME_SCROLL_ACTIVE       ((lv_color_t)LV_COLOR_MAKE(0xE0, 0xAF, 0x68))  // Yellow
    #define THEME_CAPS_WORD_ACTIVE    ((lv_color_t)LV_COLOR_MAKE(0xBB, 0x9A, 0xF7))  // Purple
    #define THEME_LOCK_INACTIVE       ((lv_color_t)LV_COLOR_MAKE(0x41, 0x4B, 0x68))  // Dark Blue-Grey
    
    #define THEME_USB_CONNECTED       ((lv_color_t)LV_COLOR_MAKE(0xFF, 0x9E, 0x64))
    #define THEME_USB_DISCONNECTED    ((lv_color_t)LV_COLOR_MAKE(0xF7, 0x76, 0x8E))
    #define THEME_BLE_CONNECTED       ((lv_color_t)LV_COLOR_MAKE(0x7A, 0xA2, 0xF7))
    #define THEME_BLE_BONDED          ((lv_color_t)LV_COLOR_MAKE(0x9E, 0xCE, 0x6A))
    #define THEME_BLE_INACTIVE        ((lv_color_t)LV_COLOR_MAKE(0x41, 0x4B, 0x68))
    
    #define THEME_WPM_START           ((lv_color_t)LV_COLOR_MAKE(0xE0, 0xAF, 0x68))
    #define THEME_WPM_END             ((lv_color_t)LV_COLOR_MAKE(0x7A, 0xA2, 0xF7))
    #define THEME_WPM_BORDER          ((lv_color_t)LV_COLOR_MAKE(0x41, 0x4B, 0x68))
    
    #define THEME_LAYER_ACTIVE        ((lv_color_t)LV_COLOR_MAKE(0x7D, 0xCF, 0xFF))
    #define THEME_LAYER_INACTIVE      ((lv_color_t)LV_COLOR_MAKE(0x41, 0x4B, 0x68))
    #define THEME_LAYER_TEXT          ((lv_color_t)LV_COLOR_MAKE(0xC0, 0xCA, 0xF5))
    
    #define THEME_BACKGROUND          ((lv_color_t)LV_COLOR_MAKE(0x1A, 0x1B, 0x26))
    #define THEME_TEXT_PRIMARY        ((lv_color_t)LV_COLOR_MAKE(0xC0, 0xCA, 0xF5))
    #define THEME_TEXT_SECONDARY      ((lv_color_t)LV_COLOR_MAKE(0x56, 0x5F, 0x89))
    #define THEME_BORDER              ((lv_color_t)LV_COLOR_MAKE(0x41, 0x4B, 0x68))
    #define THEME_INACTIVE            ((lv_color_t)LV_COLOR_MAKE(0x41, 0x4B, 0x68))

#else  // Default theme (original YADS colors)
    #define YADS_THEME_NAME "Default"
    // Battery colors use LVGL palettes
    #define THEME_BATTERY_CRITICAL    lv_palette_main(LV_PALETTE_RED)
    #define THEME_BATTERY_LOW         lv_palette_main(LV_PALETTE_ORANGE)
    #define THEME_BATTERY_MEDIUM      lv_palette_main(LV_PALETTE_YELLOW)
    #define THEME_BATTERY_GOOD        lv_palette_main(LV_PALETTE_GREEN)
    #define THEME_BATTERY_FULL        lv_palette_main(LV_PALETTE_INDIGO)
    
    #define THEME_CAPS_ACTIVE         lv_palette_main(LV_PALETTE_GREEN)
    #define THEME_NUM_ACTIVE          lv_palette_main(LV_PALETTE_INDIGO)
    #define THEME_SCROLL_ACTIVE       lv_palette_main(LV_PALETTE_PURPLE)
    #define THEME_CAPS_WORD_ACTIVE    lv_palette_main(LV_PALETTE_YELLOW)
    #define THEME_LOCK_INACTIVE       lv_palette_darken(LV_PALETTE_GREY, 3)
    
    #define THEME_USB_CONNECTED       lv_palette_main(LV_PALETTE_ORANGE)
    #define THEME_USB_DISCONNECTED    lv_palette_main(LV_PALETTE_RED)
    #define THEME_BLE_CONNECTED       lv_palette_main(LV_PALETTE_BLUE)
    #define THEME_BLE_BONDED          lv_palette_main(LV_PALETTE_GREEN)
    #define THEME_BLE_INACTIVE        lv_palette_darken(LV_PALETTE_GREY, 3)
    
    #define THEME_WPM_START           lv_palette_main(LV_PALETTE_YELLOW)
    #define THEME_WPM_END             lv_palette_main(LV_PALETTE_BLUE)
    #define THEME_WPM_BORDER          lv_palette_darken(LV_PALETTE_GREY, 3)
    
    #define THEME_LAYER_ACTIVE        lv_palette_main(LV_PALETTE_BLUE)
    #define THEME_LAYER_INACTIVE      lv_palette_darken(LV_PALETTE_GREY, 3)
    #define THEME_LAYER_TEXT          lv_color_white()
    
    #define THEME_BACKGROUND          lv_color_black()
    #define THEME_TEXT_PRIMARY        lv_color_white()
    #define THEME_TEXT_SECONDARY      lv_palette_lighten(LV_PALETTE_GREY, 2)
    #define THEME_BORDER              lv_color_white()
    #define THEME_INACTIVE            lv_palette_darken(LV_PALETTE_GREY, 3)
#endif

// Convenience macros for accessing theme colors
#define THEME_COLOR_BATTERY_CRITICAL    THEME_BATTERY_CRITICAL
#define THEME_COLOR_BATTERY_LOW         THEME_BATTERY_LOW
#define THEME_COLOR_BATTERY_MEDIUM      THEME_BATTERY_MEDIUM
#define THEME_COLOR_BATTERY_GOOD        THEME_BATTERY_GOOD
#define THEME_COLOR_BATTERY_FULL        THEME_BATTERY_FULL

#define THEME_COLOR_CAPS_ACTIVE         THEME_CAPS_ACTIVE
#define THEME_COLOR_NUM_ACTIVE          THEME_NUM_ACTIVE
#define THEME_COLOR_SCROLL_ACTIVE       THEME_SCROLL_ACTIVE
#define THEME_COLOR_CAPS_WORD_ACTIVE    THEME_CAPS_WORD_ACTIVE
#define THEME_COLOR_LOCK_INACTIVE       THEME_LOCK_INACTIVE

#define THEME_COLOR_USB_CONNECTED       THEME_USB_CONNECTED
#define THEME_COLOR_USB_DISCONNECTED    THEME_USB_DISCONNECTED
#define THEME_COLOR_BLE_CONNECTED       THEME_BLE_CONNECTED
#define THEME_COLOR_BLE_BONDED          THEME_BLE_BONDED
#define THEME_COLOR_BLE_INACTIVE        THEME_BLE_INACTIVE

#define THEME_COLOR_WPM_START           THEME_WPM_START
#define THEME_COLOR_WPM_END             THEME_WPM_END
#define THEME_COLOR_WPM_BORDER          THEME_WPM_BORDER

#define THEME_COLOR_LAYER_ACTIVE        THEME_LAYER_ACTIVE
#define THEME_COLOR_LAYER_INACTIVE      THEME_LAYER_INACTIVE
#define THEME_COLOR_LAYER_TEXT          THEME_LAYER_TEXT

#define THEME_COLOR_BACKGROUND          THEME_BACKGROUND
#define THEME_COLOR_TEXT_PRIMARY        THEME_TEXT_PRIMARY
#define THEME_COLOR_TEXT_SECONDARY      THEME_TEXT_SECONDARY
#define THEME_COLOR_BORDER              THEME_BORDER
#define THEME_COLOR_INACTIVE            THEME_INACTIVE
