#ifndef GAME_H
#define GAME_H

#include <QString>

class Game
{
public:
    virtual void setScore(int) = 0;
    virtual void setGame(int) = 0;
    virtual int getScore() const = 0;
    virtual int getGame() const = 0;
    virtual bool checkAnswer(const QString& userAnswer, const QString& expectedOutput) = 0;
};

#endif // GAME_H
