// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

namespace {
void printHands(const set<Card>& alice, const set<Card>& bob) {
  cout << "\nAlice's cards:\n";
  for (const Card& card : alice) {
    cout << card << '\n';
  }

  cout << "\nBob's cards:\n";
  for (const Card& card : bob) {
    cout << card << '\n';
  }
}
}  // namespace

int main(int argc, char** argv) {
  if (argc < 3) {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argv[1]);
  ifstream cardFile2(argv[2]);
  if (!cardFile1 || !cardFile2) {
    cout << "Could not open file " << (!cardFile1 ? argv[1] : argv[2]);
    return 1;
  }

  set<Card> alice;
  set<Card> bob;
  string suit;
  string value;
  while (cardFile1 >> suit >> value) {
    alice.emplace(suit, value);
  }

  while (cardFile2 >> suit >> value) {
    bob.emplace(suit, value);
  }

  while (true) {
    bool aliceMatched = false;
    for (auto card = alice.begin(); card != alice.end(); ++card) {
      if (bob.contains(*card)) {
        cout << "Alice picked matching card " << *card << '\n';
        bob.erase(*card);
        alice.erase(card);
        aliceMatched = true;
        break;
      }
    }

    bool bobMatched = false;
    for (auto card = bob.rbegin(); card != bob.rend(); ++card) {
      if (alice.contains(*card)) {
        cout << "Bob picked matching card " << *card << '\n';
        alice.erase(*card);
        bob.erase(*card);
        bobMatched = true;
        break;
      }
    }

    if (!aliceMatched && !bobMatched) {
      printHands(alice, bob);
      break;
    }
  }

  return 0;
}
