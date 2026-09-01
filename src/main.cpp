#include "game/Game.h"

#include "ai/AI.h"
#include "ai/Trainer.h"
#include "app/GameRunner.h"
#include "app/MainMenu.h"


int main() {
    MainMenu menu;

    while (true) {
        const MenuAction action = menu.Run();

        if (action == MenuAction::Exit)
            break;

        if (action == MenuAction::Train) {
            Game game;
            AI ai;
            Trainer trainer(game, ai);

            trainer.Load("qtable.txt");
            trainer.Train(10000, "qtable.txt");
            trainer.Save("qtable.txt");
        }

        if (action == MenuAction::Watch) {
            Game game;
            AI ai;
            Renderer renderer;

            ai.Load("qtable.txt");
            ai.SetExplorationRate(0.0f);

            GameRunner runner(game, ai, renderer);

            runner.SetMode(GameRunnerMode::AI);
            runner.SetTickRate(5.0f);

            runner.Run();
        }

        if (action == MenuAction::Play) {
            Game game;
            AI ai;
            Renderer renderer;

            GameRunner runner(game, ai, renderer);

            runner.SetMode(GameRunnerMode::Human);
            runner.SetTickRate(5.0f);

            runner.Run();
        }
    }

    return 0;
}
