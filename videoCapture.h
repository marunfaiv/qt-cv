#ifndef VIDEOCAPTURE_H
#define VIDEOVCAPTURE_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/opencv.hpp>

#define ID_CAMERA 0
#define ID_VIDEO "Otomenantoka.mp4"

class VideoCapture : public QThread
{
    Q_OBJECT
public:
    VideoCapture(QObject *parent = nullptr);
    ~VideoCapture();
    QPixmap pixmap() const
    {
        return mPixmap;
    }

protected:
    void run() override;
signals:
    void newPixmapCaptured();

private:
    QPixmap mPixmap;
    cv::Mat frame;
    cv::VideoCapture cap;

    QImage cvMatToQImage(const cv::Mat &inMat);
    QPixmap cvMatToQPixmap(const cv::Mat &inMat);
};

#endif // VIDEOCAPTURE_H