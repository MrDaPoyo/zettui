#include <unistd.h>
#include <stdio.h>

#include "canvas.h"

void editorDrawRows() {
    int y;
    for (y = 0; y<E.screenrows; y++) {
        char c = '~';

        // if (y%2) c = '-';

        char buffer[4];
        snprintf(buffer, sizeof(buffer), "%c\r\n", c);
        write(STDOUT_FILENO, buffer, 3);

        // write(STDOUT_FILENO, "~\r\n", 3); // 3 bytes, remember.
    }
}

void editorRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // \x1b is the escape character. J clears the entire (2J) screen
    write(STDOUT_FILENO, "\x1b[H", 3); // Move cursor to 1;1 (default)

    editorDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3); // 3 bytes again.
}
