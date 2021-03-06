/*
 * console_util.cpp
 *
 *  Created on: 2020/11/22
 *      Author: MunoLike
 */

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "console_util.hpp"

namespace utils {
int kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return ch;
  }

  return 0;
}
}
