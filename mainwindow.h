#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_LeftButton_pressed();

    void on_RightButton_pressed();

    void on_BackwardButton_pressed();

    void on_ForwardButton_pressed();

    void on_ForwardButton_released();

    void on_BackwardButton_released();

    void on_LeftButton_released();

    void on_RightButton_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
