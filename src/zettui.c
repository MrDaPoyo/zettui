/* 
 * Some code has been written following the "Build Your Own Text Editor" (BYOTE) guide.
 * Available at https://viewsourcecode.org/snaptoken/kilo
 * I am grateful to the creators of the booklet.
 *
 * All comments are mine, writing a bit helps me remember stuff better.
 */

// --- INCLUDES ---

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "keys.h"
#include "zettui.h"
#include "output.h"

struct termios orig_termios;

// --- TERMINAL ---

/* 
 * Just outputs an error and exits.
 */
void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    write(STDOUT_FILENO, "\x1b[?1049l", 8); // Disables alternate screen.

    perror(s);
    exit(1);
}

/*
 * Just restores the terminal.
 */
void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
    write(STDOUT_FILENO, "\x1b[?1049l", 8); // Disables alternate screen.
}
/*
 * Disable canonical mode, where each new line is held by the terminal until enter.
 * ^- This is done so that users can refine their input before sending it to the program, on enter.
 * This is unwanted, and we're going to "hijack" the terminal.
 */
void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr"); // Save a version of the terminal before entering "raw" mode. 
    atexit(disableRawMode); // And restore it once the program exits, no matter what.

    struct termios raw = orig_termios;
    write(STDOUT_FILENO, "\x1b[?1049h", 8); // Alternate screen (MUST BE DISABLED WITH "\033[?1049l")
    raw.c_iflag &= ~(ICRNL | IXON); // IXON disables Ctrl-(S,Q) that can temporarily "cut" the flow of data to the terminal.
    raw.c_oflag &= ~(OPOST); // Disable output processing (\r\n)
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // ICANON flag which disables "canonical" mode, ISIG disables Ctrl-(C,D,Y).
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_cflag |= (CS8);

    raw.c_cc[VMIN] = 0; // Bytes of input before read() can return anything.
    raw.c_cc[VTIME] = 1; // Frequency at which read()

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr"); // And apply the changes.
}


// --- INIT ---

/*
 * Waits for a keypress and handles it. Will be used to map key combos.
 */
void editorProcessKeypress() {
    char c = editorReadKey();
    switch (c) {
        case CTRL_KEY('q'):
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);

            disableRawMode();

            exit(0);
            break;
    }
}

int main() {
    enableRawMode();

    while (1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
