// card_list.cpp
// Author: Your name
// Implementation of the classes defined in card_list.h

#include "card_list.h"

#include <iostream>

CardBST::Iterator::Iterator() : node_(nullptr) {}

CardBST::Iterator::Iterator(Node* node) : node_(node) {}

const Card& CardBST::Iterator::operator*() const {
  return node_->value;
}

const Card* CardBST::Iterator::operator->() const {
  return &node_->value;
}

CardBST::Iterator& CardBST::Iterator::operator++() {
  if (node_ == nullptr) {
    return *this;
  }

  if (node_->right != nullptr) {
    node_ = CardBST::minimum(node_->right);
    return *this;
  }

  Node* parent = node_->parent;
  while (parent != nullptr && node_ == parent->right) {
    node_ = parent;
    parent = parent->parent;
  }
  node_ = parent;
  return *this;
}

CardBST::Iterator CardBST::Iterator::operator++(int) {
  Iterator previous(*this);
  ++(*this);
  return previous;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
  if (node_ == nullptr) {
    return *this;
  }

  if (node_->left != nullptr) {
    node_ = CardBST::maximum(node_->left);
    return *this;
  }

  Node* parent = node_->parent;
  while (parent != nullptr && node_ == parent->left) {
    node_ = parent;
    parent = parent->parent;
  }
  node_ = parent;
  return *this;
}

CardBST::Iterator CardBST::Iterator::operator--(int) {
  Iterator previous(*this);
  --(*this);
  return previous;
}

bool CardBST::Iterator::operator==(const Iterator& other) const {
  return node_ == other.node_;
}

bool CardBST::Iterator::operator!=(const Iterator& other) const {
  return !(*this == other);
}

CardBST::CardBST() : root_(nullptr) {}

CardBST::~CardBST() {
  destroy(root_);
}

CardBST::Node* CardBST::minimum(Node* node) {
  while (node != nullptr && node->left != nullptr) {
    node = node->left;
  }
  return node;
}

CardBST::Node* CardBST::maximum(Node* node) {
  while (node != nullptr && node->right != nullptr) {
    node = node->right;
  }
  return node;
}

void CardBST::destroy(Node* node) {
  if (node == nullptr) {
    return;
  }
  destroy(node->left);
  destroy(node->right);
  delete node;
}

CardBST::Node* CardBST::find(const Card& card) const {
  Node* current = root_;
  while (current != nullptr) {
    if (card == current->value) {
      return current;
    }
    current = card < current->value ? current->left : current->right;
  }
  return nullptr;
}

bool CardBST::insert(const Card& card) {
  Node* parent = nullptr;
  Node* current = root_;
  while (current != nullptr) {
    parent = current;
    if (card == current->value) {
      return false;
    }
    current = card < current->value ? current->left : current->right;
  }

  Node* inserted = new Node(card, parent);
  if (parent == nullptr) {
    root_ = inserted;
  } else if (card < parent->value) {
    parent->left = inserted;
  } else {
    parent->right = inserted;
  }
  return true;
}

bool CardBST::remove(const Card& card) {
  Node* target = find(card);
  if (target == nullptr) {
    return false;
  }

  if (target->left != nullptr && target->right != nullptr) {
    Node* successor = minimum(target->right);
    target->value = successor->value;
    target = successor;
  }

  Node* child = target->left != nullptr ? target->left : target->right;
  if (child != nullptr) {
    child->parent = target->parent;
  }

  if (target->parent == nullptr) {
    root_ = child;
  } else if (target == target->parent->left) {
    target->parent->left = child;
  } else {
    target->parent->right = child;
  }

  delete target;
  return true;
}

bool CardBST::contains(const Card& card) const {
  return find(card) != nullptr;
}

CardBST::Iterator CardBST::begin() const {
  return Iterator(minimum(root_));
}

CardBST::Iterator CardBST::end() const {
  return Iterator(nullptr);
}

CardBST::Iterator CardBST::rbegin() const {
  return Iterator(maximum(root_));
}

CardBST::Iterator CardBST::rend() const {
  return Iterator(nullptr);
}

void playGame(CardBST& alice, CardBST& bob) {
  while (true) {
    bool aliceMatched = false;
    for (CardBST::Iterator card = alice.begin(); card != alice.end(); ++card) {
      Card picked = *card;
      if (bob.contains(picked)) {
        std::cout << "Alice picked matching card " << picked << '\n';
        alice.remove(picked);
        bob.remove(picked);
        aliceMatched = true;
        break;
      }
    }

    bool bobMatched = false;
    for (CardBST::Iterator card = bob.rbegin(); card != bob.rend(); --card) {
      Card picked = *card;
      if (alice.contains(picked)) {
        std::cout << "Bob picked matching card " << picked << '\n';
        alice.remove(picked);
        bob.remove(picked);
        bobMatched = true;
        break;
      }
    }

    if (!aliceMatched && !bobMatched) {
      std::cout << "\nAlice's cards:\n";
      for (CardBST::Iterator card = alice.begin(); card != alice.end(); ++card) {
        std::cout << *card << '\n';
      }

      std::cout << "\nBob's cards:\n";
      for (CardBST::Iterator card = bob.begin(); card != bob.end(); ++card) {
        std::cout << *card << '\n';
      }
      break;
    }
  }
}
