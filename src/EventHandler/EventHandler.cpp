//
// Created by xw on 12/04/19.
//

#include <Common/Debug.hpp>
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

bool                EventHandler::mayClose() const
{
    return _closeWindow;
}

void                EventHandler::manageWindowEvent()
{
    if (_eventHandler.window.event == SDL_WINDOWEVENT_CLOSE ||
            (_eventHandler.type == SDL_KEYDOWN && _eventHandler.key.keysym.sym == SDLK_ESCAPE))
        _closeWindow = true;
}

const SDL_Event &EventHandler::getEventHandler() const {
    return _eventHandler;
}
