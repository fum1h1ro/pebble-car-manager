#ifndef __DIGITDRUMWINDOW_H__
#define __DIGITDRUMWINDOW_H__

enum {
  FIGURE_MAX = 10,
};

typedef struct _DigitDrumWindow {
  s32 value;
  s32 min;
  s32 max;
  s8 figure; // 整数部の桁数
  s8 realFigure; // 小数部の桁数
  s8 index;
  s16 drumWidth;
  s16 margin;
  Window* window;
  Layer* windowLayer;
  TextLayer* figures[FIGURE_MAX];
  InverterLayer* cursor;
} DigitDrumWindow;



extern DigitDrumWindow* DigitDrumWindowCreate(s32 figure, s32 real);
extern void DigitDrumWindowDestroy(DigitDrumWindow* klass);




#endif // __DIGITDRUMWINDOW_H__
