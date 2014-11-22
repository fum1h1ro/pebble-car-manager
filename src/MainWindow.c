#include "common.h"
#include "DigitDrumWindow.h"

typedef struct _MainWindow {
  Window* window;
  Layer* windowLayer;
  TextLayer* mileageLayer;
  TextLayer* efficiencyLayer;
  TextLayer* refuelLayer;
} MainWindow;

static MainWindow* _klass;

// MainWindow
static Window* _window;
static TextLayer* text_layer;
static DigitDrumWindow* _drum;


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
  _drum = DigitDrumWindowCreate(5, 1);
  window_stack_push(_drum->window, true);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Back");
  window_stack_pop(true);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
}


static TextLayer* text_layer_new(GRect rc, const char* str) {
  TextLayer* layer = text_layer_create(rc);
  text_layer_set_text(layer, str);
  text_layer_set_text_alignment(layer, GTextAlignmentRight);
  layer_add_child(_klass->windowLayer, text_layer_get_layer(layer));
  return layer;
}









static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  //layer_add_child(window_layer, text_layer_get_layer(text_layer));

  _klass->mileageLayer = text_layer_new((GRect){ .origin = { 0, 0 }, .size = { bounds.size.w, 30 } }, "50,000km");
  _klass->efficiencyLayer = text_layer_new((GRect){ .origin = { 0, 30 }, .size = { bounds.size.w, 30 } }, "10.0km/L");
  _klass->refuelLayer = text_layer_new((GRect){ .origin = { 0, 60 }, .size = { bounds.size.w, 30 } }, "Ref\nuel");
  text_layer_set_text_alignment(_klass->refuelLayer, GTextAlignmentCenter);



}

static void window_unload(Window *window) {
  text_layer_destroy(_klass->mileageLayer);
  text_layer_destroy(_klass->efficiencyLayer);
  text_layer_destroy(_klass->refuelLayer);
  text_layer_destroy(text_layer);
}










Window* MainWindowCreate() {
  //assert(_klass == NULL);
  _klass = calloc(1, sizeof(MainWindow));
  _klass->window = window_create();
  _klass->windowLayer = window_get_root_layer(_klass->window);
  window_set_click_config_provider(_klass->window, click_config_provider);
  window_set_window_handlers(_klass->window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
  });





  return _klass->window;
}
void MainWindowDestroy() {
  //assert(_klass != NULL);
  window_destroy(_klass->window);
  free(_klass);
  _klass = NULL;
}
