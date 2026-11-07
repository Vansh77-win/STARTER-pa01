#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Please provide 2 file names" << std::endl;
    return 1;
  }

  std::ifstream cardFile1(argv[1]);
  std::ifstream cardFile2(argv[2]);
  if (!cardFile1 || !cardFile2) {
    std::cout << "Could not open file " << (!cardFile1 ? argv[1] : argv[2]);
    return 1;
  }

  CardBST alice;
  CardBST bob;
  std::string suit;
  std::string value;
  while (cardFile1 >> suit >> value) {
    alice.insert(Card(suit, value));
  }

  while (cardFile2 >> suit >> value) {
    bob.insert(Card(suit, value));
  }

  playGame(alice, bob);
  return 0;
}
