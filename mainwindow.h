#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>
#include <QHostAddress>
#include "singleplayerMode.h"
#include <QFile>
#include <QProcess>
#include <QTemporaryFile>
#include <QVector>
#include "question.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_quitButton_clicked();

    void on_startButton_clicked();

    void on_singleplayerButton_clicked();

    void on_quitButton_2_clicked();

    void on_playAgainButton_clicked();

    void on_setGameButton_clicked();

    void on_playSingleButton_clicked();

    void on_answerButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
    singleplayerMode s1;
    QString sampleText;

public:
    QVector<Question> parseCSVFile();

};
static int scores = 0;

#endif // MAINWINDOW_H
