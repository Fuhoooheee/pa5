// pa5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;

#include <iostream>
#include<vector>
#include<stack>

#include <iostream>
#include "List.h"

void shuffle(List& D) {
    List left, right;
    int n = D.size();
    int mid = n / 2;
    // split the deck into left and right halves
    for (int i = 0; i < mid; i++) {
        left.moveBack(D[i]);
    }
    for (int i = mid; i < n; i++) {
        right.moveBack(D[i]);
    }
    // merge the two halves alternately
    D.clear();
    while (!left.empty() && !right.empty()) {
        D.moveBack(right.front());
        right.moveFront();
        D.moveBack(left.front());
        left.moveFront();
    }
    // add any remaining cards from the right half
    while (!right.empty()) {
        D.moveBack(right.front());
        right.moveFront();
    }
    // add any remaining cards from the left half
    while (!left.empty()) {
        D.moveBack(left.front());
        left.moveFront();
    }
}

int countShuffles(List& D) {
    List original = D;
    int count = 1;
    shuffle(D);
    while (!D.equal(original)) {
        shuffle(D);
        count++;
    }
    return count;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " max_deck_size" << std::endl;
        return 1;
    }
    int max_size = std::stoi(argv[1]);
    std::cout << "deck size\tshuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (int n = 1; n <= max_size; n++) {
        List deck;
        for (int i = 0; i < n; i++) {
            deck.moveBack(i);
        }
        int count = countShuffles(deck);
        std::cout << n << "\t\t" << count << std::endl;
    }
    return 0;
}
