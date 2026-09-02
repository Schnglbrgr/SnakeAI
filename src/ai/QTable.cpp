#include "QTable.h"

#include <fstream>
#include <iostream>


QValues& QTable::Get(const StateKey stateKey) {
    return table[stateKey];
}


size_t QTable::GetSize() const {
    return table.size();
}


void QTable::Save(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Could not save QTable: " << filename << '\n';
        return;
    }

    for (const auto& [key, values] : table) {
        file << key << " " << values.up << " " << values.down << " " << values.left << " " << values.right << "\n";
    }
}


void QTable::Load(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "No QTable found. Starting with empty QTable.\n";
        return;
    }

    table.clear();

    StateKey key;
    QValues values;

    while (file >> key >> values.up >> values.down >> values.left >> values.right) {
        table[key] = values;
    }

    std::cout << "QTable loaded: " << table.size() << " states\n";
}
