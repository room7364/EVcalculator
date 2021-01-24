#include <iostream>
#include <fstream>
#include <array>
#include <string>
const int TABLE_SIZE = 20;

bool readtable(std::array<std::array<int, TABLE_SIZE>, TABLE_SIZE>& table, const std::string& filename) {
    std::ifstream ist(filename);
    if (ist.is_open()) {
        for (int line = 0; line < TABLE_SIZE; line++)
            for (int col = 0; col < TABLE_SIZE; col++) {
                int data;
                ist >> data;
                table[line][col] = data;
            }
        return true;
    }
    else 
        return false;
}

bool writetable(const std::array<std::array<int, TABLE_SIZE>, TABLE_SIZE>& table, const std::string& filename) {
    std::ofstream ost(filename);
    if (ost.is_open()) {
        for (int line = 0; line < TABLE_SIZE; line++) {
            for (int col = 0; col < TABLE_SIZE; col++) {
                ost << table[line][col] << " ";
            }
        }
        return true;
    }
    else 
        return false;
}

void displaytable(const std::array<std::array<int, TABLE_SIZE>, TABLE_SIZE>& table) {
    for (int line = 0; line < TABLE_SIZE; line++) {
        for (int col = 0; col < TABLE_SIZE; col++) 
            std::cout << table[line][col] << " ";
        std::cout << "\n";
    }
}

void filltable(std::array<std::array<int, TABLE_SIZE>, TABLE_SIZE>& table) {
    for (int line = 0; line < TABLE_SIZE; line++) {
        for (int col = 0; col < TABLE_SIZE; col++) 
            table[line][col] = (line + 1) * (col + 1) + col;
    }
}

int main() {
    std::array<std::array<int, TABLE_SIZE>, TABLE_SIZE> table;
    std::string filename = "table.txt";

    if (readtable(table, filename)) {
        std::cout << "File has been read from " << filename << std::endl;
    }
    else {
        std::cout << "Calculating table data...\n";
        filltable(table);
        std::cout << "Writing table to file " << filename << "...";
        if (writetable(table, filename))
            std::cout << "Done.\n";
    }

    displaytable(table);
}