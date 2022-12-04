#include "Game.hpp"

int main(int argc, char* argv[]) {
    Game game;

    auto initialized = game.initialize();
    if (initialized) {
        game.run();
    }
    game.shutDown();

    return initialized ? 0 : 1;
}
