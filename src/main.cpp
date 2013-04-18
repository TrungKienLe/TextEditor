#include <vector>
#include <iostream>

#include <SDL/SDL.h>

#include "graphics/GraphicsManager.hpp"
#include "graphics/TextEditorWindow.hpp"
#include "graphics/FontRenderer.hpp"
#include "text/TextUtils.hpp"

graphics::TextEditorWindow teWin, teWin2;

int main(int argc, char **argv)
{
    if(!graphics::GraphicsManager::init("Da VIMci", 800, 600) || !graphics::FontRenderer::init())
        return false;

    teWin.init();
    teWin2.init();
    teWin2.setActive(false);
    teWin.setActive(true);
    teWin.render();

    for(bool running = true; running;)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_PAGEUP)
                    {
                        teWin2.setActive(false);
                        teWin.setActive(true);
                        teWin.render();
                        break;
                    }
                    else if(event.key.keysym.sym == SDLK_PAGEDOWN)
                    {
                        teWin.setActive(false);
                        teWin2.setActive(true);
                        teWin2.render();
                        break;
                    }

                    teWin.onKeyEvent(event.key, true);
                    teWin2.onKeyEvent(event.key, true);
                    break;
                case SDL_KEYUP:
                    teWin.onKeyEvent(event.key, false);
                    teWin2.onKeyEvent(event.key, false);
                    break;
                case SDL_VIDEORESIZE:
                    teWin.resize(event.resize.w, event.resize.h);
                    teWin2.resize(event.resize.w, event.resize.h);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    teWin.onMouseEvent(event.button, true);
                    teWin2.onMouseEvent(event.button, true);
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        teWin.update();
        teWin2.update();
        graphics::GraphicsManager::flip();
    }

    graphics::GraphicsManager::destroy();
    graphics::FontRenderer::destroy();

    return 0;
}
