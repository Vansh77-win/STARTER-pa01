// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

class CardBST {
private:
  struct Node {
    explicit Node(const Card& card, Node* parentNode = nullptr)
        : value(card), left(nullptr), right(nullptr), parent(parentNode) {}

    Card value;
    Node* left;
    Node* right;
    Node* parent;
  };

public:
  class Iterator {
  public:
    Iterator();
    const Card& operator*() const;
    const Card* operator->() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

  private:
    explicit Iterator(Node* node);
    Node* node_;

    friend class CardBST;
  };

  CardBST();
  ~CardBST();

  CardBST(const CardBST&) = delete;
  CardBST& operator=(const CardBST&) = delete;

  bool insert(const Card& card);
  bool remove(const Card& card);
  bool contains(const Card& card) const;

  Iterator begin() const;
  Iterator end() const;
  Iterator rbegin() const;
  Iterator rend() const;

private:
  Node* root_;

  static Node* minimum(Node* node);
  static Node* maximum(Node* node);
  static void destroy(Node* node);
  Node* find(const Card& card) const;
};

void playGame(CardBST& alice, CardBST& bob);

#endif
