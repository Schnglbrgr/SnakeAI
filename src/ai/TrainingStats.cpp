#include "TrainingStats.h"


void TrainingStats::Reset() {
    bestScore = 0;
    episodeCount = 0;
    totalScore = 0;
}


void TrainingStats::AddEpisode(int score) {
    episodeCount++;
    totalScore += score;
    
    if (score > bestScore)
        bestScore = score;
}


int TrainingStats::GetBestScore() const {
    return bestScore;
}


float TrainingStats::GetAverageScore() const {
    if (episodeCount == 0)
        return 0.0f;
    
    return static_cast<float>(totalScore) / episodeCount;
}
