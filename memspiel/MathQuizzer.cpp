#include "MathQuizzer.h"
#include "Display.h"

MathQuizzer::MathQuizzer() {
  difficulty = 1;
}

void MathQuizzer::createQuiz() {
  int numeroA = random(10 * difficulty);  // Generate random number taking in mind the difficulty
  int numeroB = random(10 * difficulty);
  int subtractNumber = random(10);
  resultado = -1;

  char operador;

  int operadorNum = random(4);  // random operator
    switch (operadorNum) {
    case 0:
      operador = '+';
      resultado = numeroA + numeroB;
      break;
    case 1:
      operador = '-';
      resultado = numeroA - numeroB;
      break;
    case 2:
      operador = '*';
      resultado = numeroA * numeroB;
      break;
    case 3:
      operador = '/';
      resultado = numeroA / numeroB;
      break;
  }
  
  if (resultado < 9 && resultado >= 0 ) {

    // String from the operation
    operationString = String(numeroA) + " " + operador + " " + String(numeroB) + "=";

  } else {
    int counter = 1;
    while (resultado > 9) {
      if ((resultado - subtractNumber) > 9) {
        resultado = resultado - subtractNumber;
        counter++;
      } else {
        subtractNumber = subtractNumber * counter;
      }
      operationString = String(numeroA) + " " + operador + " " + String(numeroB) + " " + "-" + " " + String(subtractNumber) + "=";
    }
    // String from the operation
  }
}




int MathQuizzer::getDifficulty() {
  return difficulty;
}

void MathQuizzer::setDifficulty(int newDifficulty) {
  difficulty = newDifficulty;
}

String MathQuizzer::getOperationString() {
  return operationString;
}

int MathQuizzer::getResultado() {
  return resultado;
}
