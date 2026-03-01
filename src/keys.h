#ifndef KEYBINDS_H
#define KEYBINDS_H

#define CTRL_KEY(k) ((k) & 0x1f)

#define EXIT_KEYBIND (CTRL_KEY('q'))

char editorReadKey();

#endif // KEYBINDS_H
