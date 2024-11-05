#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectFileButton_clicked();
    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<std::string>> data;

    void readCSV(const QString &filename);
    bool searchValueSequential(const std::string &target, double &timeTaken, std::vector<std::vector<std::string>> &foundRows, int &occurrenceCount);
    bool searchValueParallel(const std::string &target, double &timeTaken, std::vector<std::vector<std::string>> &foundRows, int &occurrenceCount);
    std::string joinRow(const std::vector<std::string> &row);
};

#endif // MAINWINDOW_H
