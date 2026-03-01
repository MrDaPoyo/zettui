#include <unistd.h>

void editorDrawRows() {
    int y;
    for (y = 0; y<24; y++) {
        write(STDOUT_FILENO, "~\r\n", 3); // 3 bytes, remember.
    }
}

void editorRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // \x1b is the escape character. J clears the entire (2J) screen
    write(STDOUT_FILENO, "\x1b[H", 3); // Move cursor to 1;1 (default)
    
    editorDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3); // 3 bytes again.
}
