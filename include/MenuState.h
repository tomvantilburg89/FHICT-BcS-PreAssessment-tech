#ifndef MENU_STATE_H
#define MENU_STATE_H

enum MenuState
{
    MAIN,
    SAVE,
    CREATE,
    STORAGE,
    PREVIEW,
    OPENING,
    PLAYING,
    STOPPED,
    NO_MENU
};

extern MenuState currentMenuState;

#endif
