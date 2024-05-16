#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->answerButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_startButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_singleplayerButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_quitButton_2_clicked()
{
    QApplication::quit();
}


void MainWindow::on_playAgainButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    s1.setGame(0);
    ui->progressBar->setValue(0);
}

void MainWindow::on_setGameButton_clicked()
{
    int temp = ui->numGame->value();
    s1.setGame(temp);
}


void MainWindow::on_playSingleButton_clicked()
{
    qDebug() << "Button pressed.";
    ui->stackedWidget->setCurrentIndex(2);
}

QVector<Question> MainWindow::parseCSVFile()
{
    QVector<Question> questions;

    QString filename = "Questions.csv"; // File name
    QFile file(filename);

    try {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw QString("Error. File cannot be opened");
        }

        QTextStream textStream(&file);
        textStream.readLine();

        while (!textStream.atEnd()) {
            QString LineData = textStream.readLine();
            QStringList values = LineData.split(',');

            // Check if there are enough fields in the line
            if (values.size() < 2) {
                throw QString("Error. Insufficient data in CSV line.");
            }

            // Extract then put them into struct
            Question question;
            question.question = values[0];
            question.expectedOutput = values[1];
            questions.append(question);
        }

        file.close();
    }
    catch (const QString &error) {
        qDebug() << error;
        if (file.isOpen()) {
            file.close();
        }
    }

    return questions;
}

void MainWindow::on_answerButton_clicked()
{
    int tempGame = s1.getGame();
    static int game = 0;
    static int i = 0;
    QVector<Question> questions = parseCSVFile();
    QString userAnswer = ui->plainTextEdit->toPlainText();

    if (s1.checkAnswer(userAnswer, questions[i].expectedOutput)) {
        qDebug() << "Correct answer";
        scores += 1;
        game += 1;
        i++;
        ui->statusLabel->setText("Correct");

    }
    else {
        scores += 0;
        game += 1;
        i++;
        ui->statusLabel->setText("Wrong");
    }
    static int value = 0;
    int incrementValue = 0;
    if (s1.getGame() == 5) {
    incrementValue = 20;
    }
    else if (s1.getGame() == 10){
    incrementValue = 10;
    }
    value += incrementValue;
    ui->progressBar->setValue(value);
    ui->progressBar->update();
    ui->score->setText(QString::number(scores) + "/" + QString::number(tempGame));
    if (game == tempGame) {
        ui->stackedWidget->setCurrentIndex(3);
        value = 0;
        ui->finalScore->setText(QString::number(scores) + "/" + QString::number(tempGame));
        game = 0;
    }

    if (!questions.isEmpty()) {
        ui->Question->setText(questions[i].question);
    }
    else {
        qDebug() << "Error";
    }

    ui->plainTextEdit->setPlainText(sampleText);
}

void MainWindow::on_loadButton_clicked()
{
    int tempGame = s1.getGame();
    sampleText = ui->plainTextEdit->toPlainText();

    QVector<Question> questions = parseCSVFile();
    if (!questions.isEmpty()) {
        ui->Question->setText(questions[0].question);
    }
    else {
        qDebug() << "Error";
    }

    ui->score->setText(QString::number(scores) + "/" + QString::number(tempGame));
    ui->loadButton->setEnabled(false);
    ui->answerButton->setEnabled(true);
}

