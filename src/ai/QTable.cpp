#include "QTable.h"

#include <fstream>

#include "raylib.h"


QValues& QTable::Get(const StateKey stateKey) {
    return table[stateKey];
}


size_t QTable::GetSize() const {
    return table.size();
}


void QTable::Save(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        TraceLog(LOG_ERROR, "Could not save QTable: %s", filename.c_str());
        return;
    }

    for (const auto& [key, values] : table) {
        file << key << " " << values.up << " " << values.down << " " << values.left << " " << values.right << "\n";
    }

    TraceLog(LOG_INFO, "QTable saved: %zu states", table.size());
}


void QTable::Load(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        TraceLog(LOG_INFO, "No QTable found. Starting with empty QTable.");
        return;
    }

    table.clear();

    StateKey key;
    QValues values;

    while (file >> key >> values.up >> values.down >> values.left >> values.right) {
        table[key] = values;
    }

    TraceLog(LOG_INFO, "QTable loaded: %zu states", table.size());
}
