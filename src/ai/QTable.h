#pragma once

#include <unordered_map>
#include <string>

#include "StateKey.h"
#include "QValues.h"


class QTable {
public:
    QValues& Get(StateKey stateKey);
    
    size_t GetSize() const;
    
    void Save(const std::string& filename) const;
    void Load(const std::string& filename);

private:
    std::unordered_map<StateKey, QValues> table;
};
