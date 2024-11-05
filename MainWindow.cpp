#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <omp.h>
#include <chrono>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(0, 155, 200)); // Pastel pink
    this->setPalette(palette);



}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::readCSV(const QString &filename) {
    std::ifstream file(filename.toStdString());
    std::string line;

    data.clear();

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> row;

        while (std::getline(ss, item, ',')) {
            row.push_back(item);
        }

        data.push_back(row);
    }
}

bool MainWindow::searchValueSequential(const std::string &target, double &timeTaken, std::vector<std::vector<std::string>> &foundRows, int &occurrenceCount) {
    auto start = std::chrono::high_resolution_clock::now();
    foundRows.clear();
    occurrenceCount = 0;

    for (const auto &row : data) {
        for (const auto &value : row) {
            if (value == target) {
                foundRows.push_back(row);
                occurrenceCount++;
                break;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeTaken = std::chrono::duration<double>(end - start).count();
    return occurrenceCount > 0;
}

bool MainWindow::searchValueParallel(const std::string &target, double &timeTaken, std::vector<std::vector<std::string>> &foundRows, int &occurrenceCount) {
    auto start = std::chrono::high_resolution_clock::now();
    foundRows.clear();
    occurrenceCount = 0;

    std::vector<std::vector<std::string>> localFoundRows;
    int localCount = 0;

#pragma omp parallel
    {
        std::vector<std::vector<std::string>> threadLocalRows;
        int threadCount = 0;

#pragma omp for schedule(static)
        for (size_t i = 0; i < data.size(); ++i) {
            for (const auto &value : data[i]) {
                if (value == target) {
                    threadLocalRows.push_back(data[i]);
                    threadCount++;
                    break;
                }
            }
        }

#pragma omp critical
        {
            foundRows.insert(foundRows.end(), threadLocalRows.begin(), threadLocalRows.end());
            occurrenceCount += threadCount;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeTaken = std::chrono::duration<double>(end - start).count();
    return occurrenceCount > 0;
}





void MainWindow::on_selectFileButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV Files (*.csv);;All Files (*)");
    if (!filename.isEmpty()) {
        ui->filePathLineEdit->setText(filename);
        readCSV(filename);
        QMessageBox::information(this, "Success", "CSV file loaded successfully.");
    }
}

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

void MainWindow::on_searchButton_clicked() {
    std::string target = ui->searchLineEdit->text().toStdString();
    double sequentialTime = 0.0, parallelTime = 0.0;
    std::vector<std::vector<std::string>> sequentialRows, parallelRows;
    int sequentialOccurrences = 0, parallelOccurrences = 0;

    bool sequentialFound = searchValueSequential(target, sequentialTime, sequentialRows, sequentialOccurrences);
    bool parallelFound = searchValueParallel(target, parallelTime, parallelRows, parallelOccurrences);

    QString message = QString("Sequential Search:\nFound: %1\nOccurrences: %2\n")
                          .arg(sequentialFound ? "Yes" : "No")
                          .arg(sequentialOccurrences);
    for (const auto &row : sequentialRows) {
        message += QString::fromStdString(joinRow(row)) + "\n";
    }

    message += QString("\nParallel Search:\nFound: %1\nOccurrences: %2\n")
                   .arg(parallelFound ? "Yes" : "No")
                   .arg(parallelOccurrences);
    for (const auto &row : parallelRows) {
        message += QString::fromStdString(joinRow(row)) + "\n";
    }

    message += QString("\nSequential Search Time: %1 seconds\nParallel Search Time: %2 seconds\nTime Difference: %3 seconds")
                   .arg(sequentialTime)
                   .arg(parallelTime)
                   .arg(parallelTime - sequentialTime);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Search Results");

    QTextEdit *textEdit = new QTextEdit(dialog);
    textEdit->setReadOnly(true);
    textEdit->setText(message);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(textEdit);
    dialog->setLayout(layout);

    dialog->resize(600, 400);
    dialog->exec();
}



std::string MainWindow::joinRow(const std::vector<std::string> &row) {
    std::ostringstream oss;
    for (const auto &value : row) {
        oss << value << " ";
    }
    return oss.str();
}
