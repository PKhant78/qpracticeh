#ifndef SINGLEPLAYERMODE_H
#define SINGLEPLAYERMODE_H

#include "game.h"
#include <QString>
#include <QFile>
#include <QProcess>
#include <QTemporaryFile>
#include <QVector>
#include <QDebug>

class singleplayerMode : public Game
{
public:

    singleplayerMode();
    void setScore(int) override;
    void setGame(int) override;
    int getScore() const override;
    int getGame() const override;
    bool checkAnswer(const QString& userAnswer, const QString& expectedOutput) override;


private:
    int score;
    int game;

};

#endif // SINGLEPLAYERMODE_H
