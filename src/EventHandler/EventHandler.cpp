//
// Created by xw on 12/04/19.
//

#include "EventHandler.hpp"

EventHandler::EventHandler():
    _closeWindow(false)
{}

EventHandler::~EventHandler() {}

void      EventHandler::wait() {
    SDL_WaitEvent(&_eventHandler);
}

SDL_WindowEventID   EventHandler::getWindowEvent() const
{
    return SDL_WindowEventID(_eventHandler.window.event);
}

bool                EventHandler::mayClose()
{
    return _closeWindow;
}

void                EventHandler::manageWindowEvent()
{
    if (_eventHandler.window.event == SDL_WINDOWEVENT_CLOSE)
        _closeWindow = true;
}