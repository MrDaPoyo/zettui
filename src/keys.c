#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "zettui.h"

char editorReadKey() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}
