#ifndef HAND_VALIDATOR_H
#define HAND_VALIDATOR_H

class HandValidator {
 public:
  enum Action { Hit, Stand, Double, Split };
  HandValidator();
  ~HandValidator();
  static const char* actionToString(HandValidator::Action a);
  static const char* handActions[4];
  static const int   hardHand[6][10];
  static const int   doubleHand[4][10];
  static const int   pairedHand[10][10];
  static const int   softHand[7][10];
};
#endif
