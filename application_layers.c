/**
* @Author: Burgy Benjamin <minidfx>
* @Date:   2016-02-16T19:19:55+01:00
* @Email:  benjamin.burgy@gmail.com
* @Last modified by:   minidfx
* @Last modified time: 2016-02-16T19:29:21+01:00
*/

#include <pebble.h>

static TextLayer *time_layer_ptr;
static TextLayer *date_layer_ptr;
static GPath *line_path_ptr;
static Layer *path_layer;

static const GPathInfo LINE_PATH_INFO = {
  .num_points = 2,
  .points = (GPoint []) {{0, 111}, {123, 111}}
};

static void draw_line_callback(Layer *layer, GContext *context) {
  line_path_ptr = gpath_create(&LINE_PATH_INFO);

  // Fill the path:
  graphics_context_set_fill_color(context, GColorBlack);
  gpath_draw_filled(context, line_path_ptr);

  // Stroke the path:
  graphics_context_set_stroke_color(context, GColorBlack);
  gpath_draw_outline(context, line_path_ptr);
}

static void display_clock(Layer *window_layer, GRect bounds) {
  // Create the TextLayer with specific bounds
  time_layer_ptr = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(70, 105), bounds.size.w, 42));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(time_layer_ptr, GColorClear);
  text_layer_set_text_color(time_layer_ptr, GColorBlack);
  text_layer_set_font(time_layer_ptr, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(time_layer_ptr, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(time_layer_ptr));
}

static void display_date(Layer *window_layer, GRect bounds) {
  // Create the TextLayer with specific bounds
  date_layer_ptr = text_layer_create(GRect(18, PBL_IF_ROUND_ELSE(70, 80), bounds.size.w, 30));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(date_layer_ptr, GColorClear);
  text_layer_set_text_color(date_layer_ptr, GColorBlack);
  text_layer_set_font(date_layer_ptr, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(date_layer_ptr, GTextAlignmentLeft);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(date_layer_ptr));
}