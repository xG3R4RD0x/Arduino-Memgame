#ifndef MATHQUIZZER_H
#define MATHQUIZZER_H

#include <Arduino.h>

class MathQuizzer {
public:
  MathQuizzer();
  void createQuiz();
  int getDifficulty();
  void setDifficulty(int newDifficulty);
  String getOperationString();
  int getResultado();

private:
  int difficulty;
  int score;
  String operationString;
  int resultado;

  const char* stringToConstChar(const String& str);
};

#endif  // MATHQUIZZER_H
