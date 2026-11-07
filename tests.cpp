#include "card_list.h"

#include <cassert>
#include <iostream>
#include <sstream>

namespace {
Card card(const char* suit, const char* value) {
  return Card(suit, value);
}

std::string captureGame(CardBST& alice, CardBST& bob) {
  std::ostringstream output;
  std::streambuf* previous = std::cout.rdbuf(output.rdbuf());
  playGame(alice, bob);
  std::cout.rdbuf(previous);
  return output.str();
}

void testInsert() {
  CardBST tree;
  assert(tree.insert(card("c", "5")));
  assert(tree.contains(card("c", "5")));
}

void testDuplicateInsert() {
  CardBST tree;
  assert(tree.insert(card("d", "8")));
  assert(!tree.insert(card("d", "8")));
}

void testContains() {
  CardBST tree;
  tree.insert(card("h", "a"));
  assert(tree.contains(card("h", "a")));
  assert(!tree.contains(card("h", "k")));
}

void testRemoveLeaf() {
  CardBST tree;
  tree.insert(card("d", "5"));
  tree.insert(card("c", "3"));
  assert(tree.remove(card("c", "3")));
  assert(!tree.contains(card("c", "3")));
  assert(tree.contains(card("d", "5")));
}

void testRemoveNodeWithTwoChildren() {
  CardBST tree;
  tree.insert(card("d", "5"));
  tree.insert(card("c", "3"));
  tree.insert(card("s", "7"));
  assert(tree.remove(card("d", "5")));
  assert(!tree.contains(card("d", "5")));
  assert(tree.contains(card("c", "3")));
  assert(tree.contains(card("s", "7")));
}

void testEmptyIterators() {
  CardBST tree;
  assert(tree.begin() == tree.end());
  assert(tree.rbegin() == tree.rend());
}

void testForwardIteration() {
  CardBST tree;
  tree.insert(card("s", "5"));
  tree.insert(card("c", "3"));
  tree.insert(card("d", "a"));
  CardBST::Iterator it = tree.begin();
  assert(*it++ == card("c", "3"));
  assert(*it++ == card("d", "a"));
  assert(*it == card("s", "5"));
  ++it;
  assert(it == tree.end());
  ++it;
  assert(it == tree.end());

  it = tree.begin();
  --it;
  assert(it == tree.end());
}

void testReverseIteration() {
  CardBST tree;
  tree.insert(card("s", "5"));
  tree.insert(card("c", "3"));
  tree.insert(card("d", "a"));
  CardBST::Iterator it = tree.rbegin();
  assert(*it == card("s", "5"));
  --it;
  assert(*it == card("d", "a"));
  --it;
  assert(*it == card("c", "3"));
}

void testPostfixIncrement() {
  CardBST tree;
  tree.insert(card("c", "2"));
  tree.insert(card("c", "4"));
  CardBST::Iterator it = tree.begin();
  CardBST::Iterator previous = it++;
  assert(*previous == card("c", "2"));
  assert(*it == card("c", "4"));
}

void testPostfixDecrement() {
  CardBST tree;
  tree.insert(card("c", "2"));
  tree.insert(card("c", "4"));
  CardBST::Iterator it = tree.rbegin();
  CardBST::Iterator previous = it--;
  assert(*previous == card("c", "4"));
  assert(*it == card("c", "2"));
}

void testGameRemovesOneMatchAndPrintsHands() {
  CardBST alice;
  CardBST bob;
  alice.insert(card("c", "3"));
  alice.insert(card("c", "8"));
  bob.insert(card("c", "3"));
  bob.insert(card("d", "4"));

  const std::string output = captureGame(alice, bob);
  assert(output ==
         "Alice picked matching card c 3\n"
         "\nAlice's cards:\n"
         "c 8\n"
         "\nBob's cards:\n"
         "d 4\n");
  assert(!alice.contains(card("c", "3")));
  assert(!bob.contains(card("c", "3")));
}

void testGameAliceThenBobMatches() {
  CardBST alice;
  CardBST bob;
  alice.insert(card("c", "2"));
  alice.insert(card("c", "3"));
  alice.insert(card("h", "2"));
  bob.insert(card("c", "3"));
  bob.insert(card("d", "4"));
  bob.insert(card("h", "2"));

  const std::string output = captureGame(alice, bob);
  assert(output ==
         "Alice picked matching card c 3\n"
         "Bob picked matching card h 2\n"
         "\nAlice's cards:\n"
         "c 2\n"
         "\nBob's cards:\n"
         "d 4\n");
  assert(!alice.contains(card("c", "3")));
  assert(!bob.contains(card("c", "3")));
  assert(!alice.contains(card("h", "2")));
  assert(!bob.contains(card("h", "2")));
}

void testGameWithNoMatchesPreservesSortedHands() {
  CardBST alice;
  CardBST bob;
  alice.insert(card("d", "2"));
  alice.insert(card("c", "5"));
  bob.insert(card("h", "9"));
  bob.insert(card("c", "3"));

  const std::string output = captureGame(alice, bob);
  assert(output ==
         "\nAlice's cards:\n"
         "c 5\n"
         "d 2\n"
         "\nBob's cards:\n"
         "c 3\n"
         "h 9\n");
  assert(alice.contains(card("d", "2")));
  assert(alice.contains(card("c", "5")));
  assert(bob.contains(card("h", "9")));
  assert(bob.contains(card("c", "3")));
}
}  // namespace

int main() {
  testInsert();
  testDuplicateInsert();
  testContains();
  testRemoveLeaf();
  testRemoveNodeWithTwoChildren();

  testEmptyIterators();
  testForwardIteration();
  testReverseIteration();
  testPostfixIncrement();
  testPostfixDecrement();

  testGameRemovesOneMatchAndPrintsHands();
  testGameAliceThenBobMatches();
  testGameWithNoMatchesPreservesSortedHands();
}
