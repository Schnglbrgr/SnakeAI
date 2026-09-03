#include "Trainer.h"

#include <iostream>


Trainer::Trainer(Game& game, AI& ai) : game(game), ai(ai) {
}


void Trainer::Train(int episodes, const std::string& saveFile) {
    std::cout << "\n=== AI TRAINING ===\n";
    std::cout << "Starting training for: " << episodes << " episodes...\n\n";

    stats.Reset();

    for (int episode = 1; episode <= episodes; episode++) {
        RunEpisode();

        stats.AddEpisode(game.GetScore());

        ai.DecayExploration();

        if (episode % 1000 == 0) {
            PrintStatistics(episode, episodes);
            Save(saveFile);
            std::cout << "QTable saved: " << saveFile << " (" << ai.GetQTableSize() << " states)\n";
        }
    }
    Save(saveFile);
    std::cout << "\n=== TRAINING COMPLETE ===\n";
    std::cout << "Episodes trained: " << episodes << '\n';
    std::cout << "QTable saved: " << saveFile << " (" << ai.GetQTableSize() << " states)\n\n";
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
