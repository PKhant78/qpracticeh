#include "singleplayerMode.h"

singleplayerMode::singleplayerMode() : score(0), game(0) {}

void singleplayerMode::setScore(int s)
{
    score = s;
}

void singleplayerMode::setGame(int g)
{
    game = g;
}

int singleplayerMode::getScore() const
{
    return score;
}

int singleplayerMode::getGame() const
{
    return game;
}

bool singleplayerMode::checkAnswer(const QString& userAnswer, const QString& expectedOutput)
{
    QTemporaryFile tempFile;
    tempFile.setFileTemplate(tempFile.fileTemplate() + ".cpp");
    if (!tempFile.open()) {
        qDebug() << "Error. Cannot open tempFile" << tempFile.fileName();
    }
    QTextStream tempStream(&tempFile);
    tempStream << userAnswer;
    tempFile.close();
    qDebug() << tempFile.fileName();

    QProcess compileProcess;
    QString compileCommand = "g++";
    QStringList compileArguments;
    compileArguments << "-o" << tempFile.fileName() + "temp"  << tempFile.fileName();
    compileProcess.start(compileCommand, compileArguments);
    compileProcess.waitForFinished(-1);

    if (compileProcess.exitCode() != 0) {
        qDebug() << "Error. Failed compiling";
        qDebug() << compileProcess.readAllStandardError();
        return false;
    }

    QProcess programProcess;
    programProcess.start(tempFile.fileName() + "temp");
    if (!programProcess.waitForStarted()) {
        qDebug() << "Error: Failed to start program";
        qDebug() << programProcess.errorString();
        return false;
    }

    programProcess.waitForFinished(-1);

    if (programProcess.exitCode() != 0) {
        qDebug() << "Error: Program exited with error code" << programProcess.exitCode();
        qDebug() << programProcess.readAllStandardError();
        return false;
    }

    QString userOutput = programProcess.readAllStandardOutput();
    qDebug() << userOutput;

    if (userOutput.trimmed() == expectedOutput.trimmed()) {
        qDebug() << "True!";
        return true;
    }
    else {
        qDebug() << "False!";
        return false;
    }
}
