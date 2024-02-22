#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <QObject>
#include <QCamera>
#include <QAudioDevice>
#include <QPermission>
#include <QAction>
#include <QMediaRecorder>
#include <QVideoWidget>
#include <QAudioInput>
#include <QMediaCaptureSession>
#include <QActionGroup>
#include <QMediaDevices>
#include <QCameraDevice>
#include <QApplication>

class MyCamera : public QObject
{
    Q_OBJECT
    QScopedPointer<QAudioInput> m_audioInput;
    QMediaDevices m_devices;
    QAction *actionStartCamera;
    QAction *actionStopCamera;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

public:
    explicit MyCamera(QObject *parent = nullptr);

    QMediaCaptureSession m_captureSession;
    QScopedPointer<QCamera> m_camera;
    QActionGroup *videoDevicesGroup = nullptr;

    void camera_init();
    void updateCameraActive(bool active);
    void startCamera();
    void stopCamera();
signals:

private:

};

#endif // MYCAMERA_H
