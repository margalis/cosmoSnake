#include "snake.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QBrush>
#include <QImage>
#include <QGraphicsScene>
#include <QColor>
#include <QTime>
#include <QMediaPlayer>

Snake::Snake(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:black;"); //darkblue ov el norm a
    //setStyleSheet("background-image: /resources/img/space.png ");
    //setBackgroundBrush(QBrush(QImage(":/resources/img/space.png")));
    //setStyleSheet("background-image: url(C:/Users/User/Desktop/space.png);");
    //  url(./image.png) chegaaav fony T_T,dont know what to do

    // ughghutunnery yst chashaki, im mot gnum a depi aj
    leftDirection = false;
    rightDirection = false; // depi aj er
    upDirection = false;
    downDirection = true; // nerqev, :stugum
    inGame = true; // khaghi mej enq

    setFixedSize(B_WIDTH, B_HEIGHT); // size

    loadImages(); // imagenery
    // music filery
    mc->setMedia(QUrl("C:/Users/User/Downloads/Daft-Punk-Veridis-Quo.mp3"));
    fail->setMedia(QUrl("C:/Users/User/Downloads/bonk_BEtiM8g.mp3"));
    initGame();
    // starting mode y
}

void Snake::loadImages() { // ok arden

    dot.load("C:\\Users\\User\\Desktop\\dot.png");
    head.load("C:\\Users\\User\\Desktop\\head.png");
    apple.load("C:\\Users\\User\\Desktop\\apple.png");
    planet1.load("C:\\Users\\User\\Desktop\\planet1.png");
    planet2.load("C:\\Users\\User\\Desktop\\planet2.png");
    planet3.load("C:\\Users\\User\\Desktop\\planet3.png");
}

void Snake::initGame() {
    mc->play();
    dots = 3; // skzbic marminy 2 hatanoc a

   /* QGraphicsTextItem * score= new QGraphicsTextItem();
    score->setPlainText(QString("Score: ") + QString::number(countofEatenApples));
 // chstacvec senc */

    for (int z = 0; z < dots; z++) {
        x[z] = 100 - z * 10;  // ed 3 doteri koo nern enq voroshum
        y[z] = 100;   // horizonakan dirqum enq sksum eli,dra hamar yy chenq poxum
    }

    locateApple();  // random appley mi te qcum enq

    timerId = startTimer(DELAY); // timery dnum enq gortsi
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e); //es zut vor chkhosi  e-i vra

    doDrawing();
}

void Snake::doDrawing() {
    //este nkarum enq snake in u apple nerin
    QPainter qp(this);

        qp.drawImage(X_Pl11,Y_Pl11,planet1);   //200,200 sranc kpnelis pochy erkarum a
        qp.drawImage(X_Pl12,Y_Pl12,planet1);   //20,250
        qp.drawImage(250,20,planet1);          //random planet e, ughghaki khaghacoghin sheghelu hamar

        qp.drawImage(30,100,planet3);          //decorative
        qp.drawImage(200,50,planet3);
        qp.drawImage(50,200,planet3);
        qp.drawImage(100,120,planet3);

        qp.drawImage(X_Pl21,Y_Pl21,planet2);  //kpnelis traqvum a
        qp.drawImage(X_Pl22,Y_Pl22,planet2); // same
        qp.drawImage(250,250,planet2);


    if (inGame) { // ete khaghi mej enq

        qp.drawImage(apple_x, apple_y, apple); // drinq appley

        for (int z = 0; z < dots; z++) { //snake y
            if (z == 0) {
                qp.drawImage(x[z], y[z], head); //ete arajin dotn a -> headn  a
                // petq a arandznacnel vor collision y karananq fixenq
            } else {
                qp.drawImage(x[z], y[z], dot); // mnacats marmni masery
            }
        }

    } else {
        // khagi verj
        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp) {

    QString message = "Game over nakhshoon jan";
    QString message1= "to restart click SPACE key";
    QString message2= "Score:"+ QString::number(countofEatenApples);
    //fonty u rotationy
    QFont font("TypeWriter", 15, QFont::ExtraBold);
    QFont font1("TypeWriter", 10, QFont::DemiBold);
    QFont font2("TypeWriter", 10, QFont::DemiBold);
    QFontMetrics fm(font);
    QFontMetrics fm1(font1);
    QFontMetrics fm2(font2);
    int textWidth = fm.horizontalAdvance(message);
    int text1Width =fm1.horizontalAdvance(message1);
    int text2Width =fm2.horizontalAdvance(message2);
    //guyny
    QColor clr= Qt::yellow;
    QColor clr1=Qt::magenta;
    QColor clr2=Qt::darkMagenta;
    qp.setFont(font);
    qp.setPen(clr);
    int h = height();
    int w = width();

    //zut geometryn
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);

    qp.setFont(font1);
    qp.setPen(clr1);

    qp.drawText(-text1Width/2,16,message1);

    qp.setFont(font2);
    qp.setPen(clr2);
    qp.drawText(-text2Width/2,32,message2);
}

void Snake::checkApple() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        //ete heady u apple y  hamynkel en
        dots++; // snaky erkarec
        countofEatenApples++;   //score y
        locateApple(); //random alg
    }
}

void Snake::move() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
        //irakanum menak headn a sharjvum, mnacasy ay senc
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE; //depi dzax gnalis heady OX koon -1
    }

    if (rightDirection) {// depi aj gnalis heady OX koon +1
        x[0] += DOT_SIZE;
    }

    if (upDirection) {//depi verev gnalis heady Oy koon -1
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {//depi nerqev gnalis heady Oy koon +1
        y[0] += DOT_SIZE;
    }
}

void Snake::checkPl2Collision(){
    if(x[0]==X_Pl21 && y[0]==Y_Pl21){
        dots++;
    }
    if(x[0]==X_Pl22 && y[0]==Y_Pl22){
        dots++;
    }
}
void Snake::checkCollision() {
        // dxkac paterin  kam inqy iran kerav
    for (int z = dots; z > 0; z--) {

        if (((z > 4) && (x[0] == x[z]) && (y[0] == y[z]))) {
           fail->play();    //soundy

            inGame = false;  // inqn iran utely , 4ic poqreri depqum hnaravor chi
        }
    }

// sahmanneric durs ekats vichaky
    if (y[0] >= B_HEIGHT) {
         fail->play();
        inGame = false;
    }

    if (y[0] < 0) {
       fail->play();
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
         fail->play();
        inGame = false;
    }

    if (x[0] < 0) {
        fail->play();
        inGame = false;
    }
    //planetihet crashy
    if(x[0]==X_Pl11 && y[0]==Y_Pl11){
        fail->play();
        inGame = false;
    }
    if(x[0]==X_Pl12 && y[0]==Y_Pl12){
        fail->play();
        inGame = false;
    }

    if(!inGame) {
        mc->stop();//musicy verj

        killTimer(timerId); //fsyo
    }
}

void Snake::locateApple() {
    //voroshuma apple i random possitiony
    // ogtvel em internetic :DDD
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {
  // khaghi yntacqn a sarqum , khodi a qcum eli
    Q_UNUSED(e);

    if (inGame) {

        checkApple();
        checkCollision();
        checkPl2Collision();
        move();
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {
    //steghnashari het kapy
    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }
    if((key==Qt::Key_Space) && (!inGame) /* &&(!upDirection) && (!downDirection)
            && (!leftDirection) &&(!rightDirection)*/)
    {
        inGame=true;
        leftDirection = false;
        rightDirection = true; // depi aj
        upDirection = false;
        downDirection = false;
        initGame();    }
    QWidget::keyPressEvent(e);
}
