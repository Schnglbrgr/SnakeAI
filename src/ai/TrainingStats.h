#pragma once


class TrainingStats {
public:
    void Reset();
    void AddEpisode(int score);
    int GetBestScore() const;
    float GetAverageScore() const;
    
private:
    int bestScore = 0;
    int episodeCount = 0;
    int totalScore = 0;
};


