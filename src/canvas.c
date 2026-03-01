#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "zettui.h"
#include "canvas.h"

struct canvasConfig E;

int getWindowSize(int *rows, int *cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

void initCanvas(void) {
    if (getWindowSize(&E.screenrows, &E.screencols) == -1)
        die("getWindowSize");
}

