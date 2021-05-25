#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QMenu>
#include <QAction>
#include <QMediaPlayer>


class Snake : public QWidget {
        Q_OBJECT
public:
      Snake(QWidget *parent = nullptr);

protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);
private:
      QImage dot; // marmni masery
      QImage head; // gluxy
      QImage apple; // khndzory`  bolory 10x10pxem vercrel
      QImage planet1;  // pochiky erkaracnum e
      QImage planet2; // endgame
      QImage planet3;  // decorative

      QMediaPlayer* mc= new QMediaPlayer(); //background musicy
      QMediaPlayer* fail = new QMediaPlayer(); // faili BONK y

      static const int B_WIDTH = 300; // boardi laynutyuny
      static const int B_HEIGHT = 300; // erkarutyuny
      static const int DOT_SIZE = 10; // keti koghmy` nenc em vercrel, vor
      // ev oci marmni masery ev khndory 10px en(karanq vercnenq aveli poqr)
      static const int ALL_DOTS = 886; //maximum qani dot kara lini boardum
      // de nay` amen doti makeresy `100  boardi makeresy`300*300=>
      // 300*300 / 100 = 900 hatik  -  4 hat planet
      static const int RAND_POS = 20; // khndzori random koordinat a voroshum
      static const int DELAY = 149; // aragutyunn a khaghi(eli karanq poxenq)

      int countofEatenApples=0;  // score

      int timerId;
      int dots;
      int apple_x; //
      int apple_y; // apple i koo nery

      int x[ALL_DOTS]; // snake i bolooor maseri koo neri arrayner
      int y[ALL_DOTS];

      const int X_Pl11= 200;
      const int Y_Pl11= 200;
      const int X_Pl12= 20;  // PLanet 1ery
      const int Y_Pl12= 250;

      const int X_Pl21=150;
      const int Y_Pl21=50;
      const int X_Pl22=80; // Planet 2nery
      const int Y_Pl22=150;
      //ughhghutyunnery
      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;
      bool inGame;
public:
      void loadImages();
      void initGame();
      void locateApple();
      void checkApple();
      void checkCollision();
      void checkPl2Collision();
      void move();
      void doDrawing();
      void gameOver(QPainter &);
};
#endif // SNAKE_H
