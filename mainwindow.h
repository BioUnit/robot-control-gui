#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioInput>
#include <QMediaCaptureSession>
#include <QActionGroup>
#include <QMediaDevices>
#include <QCameraDevice>
#include "tcpsocket.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    TcpSocket s;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void camera_init();
    void updateCameras();
    void setCamera(const QCameraDevice &cameraDevice);
    void updateCameraActive(bool active);
    void startCamera();
    void stopCamera();

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
    QScopedPointer<QAudioInput> m_audioInput;
    QMediaCaptureSession m_captureSession;
    QActionGroup *videoDevicesGroup = nullptr;
    QMediaDevices m_devices;
    QScopedPointer<QCamera> m_camera;
    QAction *actionStartCamera;
    QAction *actionStopCamera;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;
};
#endif // MAINWINDOW_H
