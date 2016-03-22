/**
* @Author: Burgy Benjamin <minidfx>
* @Date:   2016-02-16T19:19:55+01:00
* @Email:  benjamin.burgy@gmail.com
* @Last modified by:   minidfx
* @Last modified time: 2016-03-22T21:11:30+01:00
*/

#include <pebble.h>
#include "layers.h"

static TextLayer *time_layer_ptr;
static TextLayer *date_layer_ptr;
static GPath *line_path_ptr;
static Layer *path_layer;
static Layer *battery_path_layer;
static TextLayer *battery_layer_ptr;
static TextLayer *week_day_layer_ptr;

static Layer *window_layer;
static GRect window_bounds;

static uint8_t charge_percent = 0;
static uint8_t textPaddingLeft = 15;

void handle_minute(struct tm *tick_time, TimeUnits units_changed)
{
    update_time(tick_time);
}

void update_time(struct tm *tick_time)
{
    static char s_time_buffer[8];
    static char s_date_buffer[12];
    static char s_week_day_buffer[15];

    strftime(s_time_buffer, sizeof(s_time_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
    strftime(s_date_buffer, sizeof(s_date_buffer), "%B %d", tick_time);
    strftime(s_week_day_buffer, sizeof(s_week_day_buffer), "%A", tick_time);

    text_layer_set_text(time_layer_ptr, s_time_buffer);
    text_layer_set_text(date_layer_ptr, s_date_buffer);
    text_layer_set_text(week_day_layer_ptr, s_week_day_buffer);
}

void handle_battery(BatteryChargeState charge_state)
{
    update_battery_line(charge_state.charge_percent);
}

void init_window_layer(Window *window)
{
    // Get information about the Window
    window_layer = window_get_root_layer(window);
    window_bounds = layer_get_bounds(window_layer);
}

void draw_line_callback(Layer *layer, GContext *context)
{
    GPoint start = GPoint(0, 111);
    GPoint end = GPoint(122, 111);

    graphics_draw_line(context, start, end);
}

void draw_line()
{
    path_layer = layer_create(window_bounds);
    layer_set_update_proc(path_layer, draw_line_callback);
    layer_add_child(window_layer, path_layer);
}

void draw_battery_line_callback(Layer *layer, GContext *context)
{
    uint8_t lineHeight = charge_percent * window_bounds.size.h / 100;
    GRect rect_bounds = GRect(window_bounds.size.w - 4, lineHeight, window_bounds.size.w, window_bounds.size.h);

    // Draw a rectangle
    graphics_draw_rect(context, rect_bounds);

    // Fill rectangle
    graphics_fill_rect(context, rect_bounds, 0, GCornersAll);
}

void draw_battery_line()
{
    battery_path_layer = layer_create(window_bounds);
    layer_set_update_proc(battery_path_layer, draw_battery_line_callback);
    layer_add_child(window_layer, battery_path_layer);
}

void update_battery_line(uint8_t percent)
{
    charge_percent = 100 - percent;
    layer_mark_dirty(battery_path_layer);
}

void display_clock()
{
    time_layer_ptr = text_layer_create(GRect(textPaddingLeft, PBL_IF_ROUND_ELSE(70, 105), window_bounds.size.w - textPaddingLeft, 42));

    // Improve the layout to be more like a watchface
    text_layer_set_background_color(time_layer_ptr, GColorClear);
    text_layer_set_text_color(time_layer_ptr, GColorBlack);
    text_layer_set_font(time_layer_ptr, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
    text_layer_set_text_alignment(time_layer_ptr, GTextAlignmentLeft);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_layer, text_layer_get_layer(time_layer_ptr));
}

void display_date()
{
    date_layer_ptr = text_layer_create(GRect(textPaddingLeft, PBL_IF_ROUND_ELSE(70, 80), window_bounds.size.w - textPaddingLeft, 30));

    // Improve the layout to be more like a watchface
    text_layer_set_background_color(date_layer_ptr, GColorClear);
    text_layer_set_text_color(date_layer_ptr, GColorBlack);
    text_layer_set_font(date_layer_ptr, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(date_layer_ptr, GTextAlignmentLeft);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_layer, text_layer_get_layer(date_layer_ptr));
}

void display_week_day()
{
    week_day_layer_ptr = text_layer_create(GRect(textPaddingLeft, PBL_IF_ROUND_ELSE(50, 60), window_bounds.size.w - textPaddingLeft, 30));

    // Improve the layout to be more like a watchface
    text_layer_set_background_color(week_day_layer_ptr, GColorClear);
    text_layer_set_text_color(week_day_layer_ptr, GColorBlack);
    text_layer_set_font(week_day_layer_ptr, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(week_day_layer_ptr, GTextAlignmentLeft);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_layer, text_layer_get_layer(week_day_layer_ptr));
}

void destroy_application_layers()
{
    text_layer_destroy(time_layer_ptr);
    text_layer_destroy(battery_layer_ptr);
    text_layer_destroy(week_day_layer_ptr);
    layer_destroy(path_layer);
    gpath_destroy(line_path_ptr);
    layer_destroy(battery_path_layer);
}