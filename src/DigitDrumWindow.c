#include "common.h"
#include "DigitDrumWindow.h"

static char* digits[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static s32 pow_(s32 v, s32 c) {
  s32 r = 1;
  for (int i = 0; i < c; ++i) {
    r *= v;
  }
  return r;
}

static void update_figures(DigitDrumWindow* klass) {
  char fmt[FIGURE_MAX+1], str[FIGURE_MAX+1];
  if (klass->realFigure > 0) {
    snprintf(fmt, FIGURE_MAX+1, "%%0%dd.%%0%dd", klass->figure, klass->realFigure);
    s32 denom = (klass->realFigure > 0)? pow_(10, klass->realFigure) : 0;
    s32 i = klass->value / denom;
    s32 r = klass->value % denom;
    snprintf(str, FIGURE_MAX+1, fmt, i, r);
  } else {
    snprintf(fmt, FIGURE_MAX+1, "%%0%dd", klass->figure);
    snprintf(str, FIGURE_MAX+1, fmt, klass->value);
  }
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %s %s", fmt, str);
  const s16 num = klass->figure + klass->realFigure + ((klass->realFigure > 0)? 1 : 0);
  for (int i = 0; i < num; ++i) {
    TextLayer* l = klass->figures[i];
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", str[i] - '0');
    if (str[i] == '.') {
      text_layer_set_text(l, ".");
    } else {
      text_layer_set_text(l, digits[str[i] - '0']);
    }
  }
}


static void create_figures(DigitDrumWindow* klass, s32 figure, s32 real) {
  const GRect bounds = layer_get_bounds(klass->windowLayer);
  const s16 num = figure + real + ((real > 0)? 1 : 0);
  klass->drumWidth = bounds.size.w / num; // 一つのサイズ
  klass->margin = bounds.size.w - klass->drumWidth * num;
  GRect rc = { .origin = { klass->margin, 30 }, .size = { klass->drumWidth, 30 } };
  for (int i = 0; i < num; ++i) {
    TextLayer* l = klass->figures[i] = text_layer_create(rc);
    text_layer_set_text(l, "0");
    text_layer_set_text_alignment(l, GTextAlignmentCenter);
    layer_add_child(klass->windowLayer, text_layer_get_layer(l));
    rc.origin.x += klass->drumWidth;
  }
}
static void destroy_figures(DigitDrumWindow* klass) {
}
static void create_cursor(DigitDrumWindow* klass) {
  const GRect bounds = layer_get_bounds(klass->windowLayer);
  GRect rc = { .origin = { klass->margin, 30 }, .size = { klass->drumWidth, 30 } };
  klass->cursor = inverter_layer_create(rc);
  layer_add_child(klass->windowLayer, inverter_layer_get_layer(klass->cursor));
}

static void select_click_handler(ClickRecognizerRef recognizer, void* context) {
  DigitDrumWindow* klass = (DigitDrumWindow*)context;
  //if (klass->index <= 0) {
  //} else {
    ++klass->index;
  //}
  GRect rc = { .origin = { klass->margin + klass->drumWidth * klass->index, 30 }, .size = { klass->drumWidth, 30 } };
  layer_set_frame(inverter_layer_get_layer(klass->cursor), rc);
  //text_layer_set_text(text_layer, "Select");
}
static void up_click_handler(ClickRecognizerRef recognizer, void* context) {
  //text_layer_set_text(text_layer, "Up");








}
static void down_click_handler(ClickRecognizerRef recognizer, void* context) {
  //text_layer_set_text(text_layer, "Down");
}
static void back_click_handler(ClickRecognizerRef recognizer, void* context) {
  DigitDrumWindow* klass = (DigitDrumWindow*)context;
  if (klass->index <= 0) {
    window_stack_pop(true);
  } else {
    --klass->index;
  }
  GRect rc = { .origin = { klass->margin + klass->drumWidth * klass->index, 30 }, .size = { klass->drumWidth, 30 } };
  layer_set_frame(inverter_layer_get_layer(klass->cursor), rc);
  //text_layer_set_text(text_layer, "Back");
}
static void click_config_provider(void* context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_set_click_context(BUTTON_ID_SELECT, context);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_set_click_context(BUTTON_ID_UP, context);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_set_click_context(BUTTON_ID_DOWN, context);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
  window_set_click_context(BUTTON_ID_BACK, context);
}
DigitDrumWindow* DigitDrumWindowCreate(s32 figure, s32 real) {
  //assert(_klass == NULL);
  DigitDrumWindow* klass = calloc(1, sizeof(DigitDrumWindow));
  klass->window = window_create();
  klass->windowLayer = window_get_root_layer(klass->window);
  klass->figure = figure;
  klass->realFigure = real;
  klass->index = 0;

  create_figures(klass, figure, real);
  update_figures(klass);
  create_cursor(klass);



  window_set_click_config_provider_with_context(klass->window, click_config_provider, klass);
  //window_set_window_handlers(klass->window, (WindowHandlers) {
  //    .load = window_load,
  //    .unload = window_unload,
  //});





  return klass;
}
void DigitDrumWindowDestroy(DigitDrumWindow* klass) {
  //assert(_klass != NULL);
  window_destroy(klass->window);
  free(klass);
}
