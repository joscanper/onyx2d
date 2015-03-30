#include <iostream>

#include "../../onyx2d.h"

#include "include/Game.h"

using namespace std;
using namespace onyx2d;

#define GAME_WIDTH 800
#define GAME_HEIGHT 600

// Main function
int main(int argc, char **argv)
{

    Core()->Init();
    RenderMngr()->DeviceStart(GAME_WIDTH, GAME_HEIGHT, false, "Onyx Illusion : Game DEMO", argc, argv);
    RenderMngr()->ClearColor.Set(0.0f,0.0f,0.0f);

    Game *game = new Game();

    bool done = false;
    while (!done)
    {
        Core()->Update();
        game->Update(done);
    }

    game->Dispose();
    Core()->Dispose();
    return 0;

}



