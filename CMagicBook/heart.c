#include <ncurses.h>

/* --------------------------------------------------------------
  viewheart -- 座標を指定してハートマークを描く
   -------------------------------------------------------------- */
void viewheart(int x, int y)
{
  int i;
  char heart[8][32 + 1] = {
    " ****      ****",
    "******    ******",
    "*******  *******",
    " **************",
    "   **********",
    "    ********",
    "      ****",
    "       **"
  };

  for (i = 0; i < 8; i++) {
    mvprintw(y+i, x, heart[i]);
  }
}

/* --------------------------------------------------------------
  clrheart -- 座標を指定してハートマークを消す
   -------------------------------------------------------------- */
void clrheart(int x, int y)
{
  int i;
  /* 他の形にも対応できるよう矩形領域をスペースで消す */
  char clr[8][32 + 1] = {
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
  };

  for (i = 0; i < 8; i++) {
    mvprintw(y+i, x, clr[i]);
  }

/* 
  clr[] = "                ";
    と宣言しておいて
  for (i = 0; i < 8; i++) {
    mvprintw(y+i, x, clr);
  }
    のようにしてもOK。
 */
}

/* --------------------------------------------------------------
  moveheart -- 矢印キーでハートマークを動かす
   -------------------------------------------------------------- */
void moveheart(int x, int y)
{
  int key = 0;
  int oldx, oldy;
  /* [ESC]キーが押されるまで繰り返す */
  while ((key = getch()) != KEY_ESC) {
    switch (key) {
    case KEY_UP :
      oldx = x;
      oldy = y;
      y--;
      if (y < 0) y = 0;
      break;
    case KEY_DOWN :
      oldx = x;
      oldy = y;
      y++;
      if (y > 17) y = 17;
      break;
    case KEY_LEFT :
      oldx = x;
      oldy = y;
      x--;
      if (x < 0) x = 0;
      break;
    case KEY_RIGHT :
      oldx = x;
      oldy = y;
      x++;
      if (x > 63) x = 63;
      break;
    }
    /* ハートを描く */
    clrheart(oldx, oldy);
    viewheart(x, y);
  }
}

/* --------------------------------------------------------------
  main
   -------------------------------------------------------------- */
int main(void)
{
  int i;
  int x, y;
  int oldx, oldy;

  initscr();

  /* 特殊キーを受け取る */
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  /* 初期座標 */
  x = 32;
  y = 8;

  viewheart(x, y);  /* ハートを表示 */
  moveheart(x, y);      /* キーでハートを動かす */

  endwin();
  return (0);
}
