#include <unistd.h>

void editorRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // \x1b is the escape character. J clears the entire (2J) screen
    write(STDOUT_FILENO, "\x1b[H", 3); // Move cursor to 1;1 (default)
}
