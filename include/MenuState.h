#ifndef MENU_STATE_H
#define MENU_STATE_H

enum MenuState
{
    MAIN,
    CREATE,
    STORAGE,
    PREVIEW,
    PLAYING,
    STOPPED,
    NO_MENU
};

extern MenuState currentMenuState;

#endif
