// card.h
// Author: Your name
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iosfwd>
#include <string>

class Card {
public:
  Card(const std::string& suit, const std::string& value);

  bool operator==(const Card& other) const;
  bool operator<(const Card& other) const;
  bool operator>(const Card& other) const;

  friend std::ostream& operator<<(std::ostream& out, const Card& card);

private:
  int suit_;
  int value_;
};

#endif
