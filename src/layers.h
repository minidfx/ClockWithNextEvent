/**
* @Author: Burgy Benjamin <minidfx>
* @Date:   2016-03-22T20:22:31+01:00
* @Email:  benjamin.burgy@gmail.com
* @Last modified by:   minidfx
* @Last modified time: 2016-03-25T10:00:43+01:00
*/

#include <pebble.h>

void init_window_layer(Window *window);
void draw_line_callback(Layer *layer, GContext *context);
void draw_line();
void draw_battery_line_callback(Layer *layer, GContext *context);
void draw_battery_line();
void draw_bluetooth();
void update_battery_line(uint8_t percent);
void draw_time();
void draw_date();
void draw_week_day();
void destroy_application_layers();
void update_datetime(struct tm *tick_time);

void load_resources();

void handle_app_connection_handler(bool connected);
void handle_minute(struct tm *tick_time, TimeUnits units_changed);
void handle_battery(BatteryChargeState charge_state);
