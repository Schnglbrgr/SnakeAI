#include "Trainer.h"

#include <iostream>


Trainer::Trainer(Game& game, AI& ai) : game(game), ai(ai) {
}


void Trainer::RunEpisode() const {
    game.Reset();

    while (!game.IsGameOver()) {
        const GameState state = game.GetGameState();

        const Action action = ai.GetAction(state);

        const StepResult result = game.Step(action);

        ai.Learn(state, action, result.reward, result.state);
    }
}


void Trainer::Train(int episodes, const std::string& saveFile) {
    stats.Reset();

    for (int episode = 1; episode <= episodes; episode++) {
        RunEpisode();

        stats.AddEpisode(game.GetScore());

        ai.DecayExploration();

        PrintStatistics(episode, episodes);

        if (episode % 100 == 0) {
            Save(saveFile);
            std::cout << "QTable saved: " << saveFile << '\n';
        }
    }
    Save(saveFile);
    std::cout << "Training complete. QTable saved: " << saveFile << '\n';
}


void Trainer::PrintStatistics(const int episode, const int totalEpisodes) const {
    std::cout << "Episode " << episode << " / " << totalEpisodes << " | Score: " << game.GetScore() << " | Best: " <<
        stats.GetBestScore() << " | Avg: " << stats.GetAverageScore() << " | Steps: " << game.GetSteps() <<
        " | Epsilon: " << ai.GetExplorationRate() << " | States: " << ai.GetQTableSize() << '\n';
}


void Trainer::Load(const std::string& filename) const {
    ai.Load(filename);
}


void Trainer::Save(const std::string& filename) const {
    ai.Save(filename);
}
