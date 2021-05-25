#include <QApplication>
#include "snake.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Snake game;

  game.setWindowTitle("SPACE COWBOY SNAKE & APPLE");
  game.show();

  return app.exec();
}
