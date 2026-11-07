// card.cpp
// Author: Your name
// Implementation of the classes defined in card.h

#include "card.h"

#include <ostream>
#include <stdexcept>

namespace {
int suitRank(const std::string& suit) {
  if (suit == "c") {
    return 1;
  }
  if (suit == "d") {
    return 2;
  }
  if (suit == "s") {
    return 3;
  }
  if (suit == "h") {
    return 4;
  }
  throw std::invalid_argument("Invalid card suit: " + suit);
}

int valueRank(const std::string& value) {
  if (value == "a") {
    return 1;
  }
  if (value == "j") {
    return 11;
  }
  if (value == "q") {
    return 12;
  }
  if (value == "k") {
    return 13;
  }
  if (value == "10") {
    return 10;
  }
  if (value.size() == 1 && value[0] >= '2' && value[0] <= '9') {
    return value[0] - '0';
  }
  throw std::invalid_argument("Invalid card value: " + value);
}

const char* suitName(int suit) {
  static const char* suits[] = {"c", "d", "s", "h"};
  return suits[suit - 1];
}

const char* valueName(int value) {
  static const char* values[] = {
      "a", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k"};
  return values[value - 1];
}
}  // namespace

Card::Card(const std::string& suit, const std::string& value)
    : suit_(suitRank(suit)), value_(valueRank(value)) {}

bool Card::operator==(const Card& other) const {
  return suit_ == other.suit_ && value_ == other.value_;
}

bool Card::operator<(const Card& other) const {
  return suit_ < other.suit_ ||
         (suit_ == other.suit_ && value_ < other.value_);
}

bool Card::operator>(const Card& other) const {
  return other < *this;
}

std::ostream& operator<<(std::ostream& out, const Card& card) {
  return out << suitName(card.suit_) << ' ' << valueName(card.value_);
}
