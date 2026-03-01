#ifndef CANVAS_H
#define CANVAS_H

#include <termios.h>

struct canvasConfig {
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

extern struct canvasConfig E;

void initCanvas(void);

#endif // CANVAS_H

