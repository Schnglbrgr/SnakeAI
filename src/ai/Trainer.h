#pragma once

#include "../ai/AI.h"
#include "../game/Game.h"
#include "TrainingStats.h"


class Trainer {
public:
    Trainer(Game& game, AI& ai);
    
    void Train(int episodes, const std::string& saveFile);
    
    void Load(const std::string& filename) const;
    void Save(const std::string& filename) const;
    
private:
    void RunEpisode() const;
    void PrintStatistics(int episode, int totalEpisodes) const;
    
    Game& game;
    AI& ai;
    
    TrainingStats stats;
};