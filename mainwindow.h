#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpsocket.h"
#include "mycamera.h"
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    TcpSocket my_socket;
    MyCamera my_camera;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateCameras();
    void setCamera();
    void initSignals();
    QMediaPlayer *player;
private slots:
    void LeftButton_pressed();
    void RightButton_pressed();
    void BackwardButton_pressed();
    void ForwardButton_pressed();
    void ForwardButton_released();
    void BackwardButton_released();
    void LeftButton_released();
    void RightButton_released();
    void TcpConnButton_clicked();
    void KeyboardSwitchButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
