//
// Created by xw on 12/04/19.
//

#ifndef RT_EVENTHANDLER_HPP
#define RT_EVENTHANDLER_HPP

#include <SDL_events.h>

class   EventHandler {

public:
    EventHandler();
    ~EventHandler();

    void        wait();
    void        manageWindowEvent();

    bool        mayClose();


    SDL_WindowEventID     getWindowEvent() const;

private:
    SDL_Event           _eventHandler;

private:
    bool                _closeWindow;

};

#endif //RT_EVENTHANDLER_HPP
