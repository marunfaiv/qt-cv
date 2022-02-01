#include "videoCapture.h"
#include <QDebug>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std::chrono;

VideoCapture::VideoCapture(QObject *parent)
    : QThread{parent}, cap{ID_VIDEO}
{
}

VideoCapture::~VideoCapture()
{
    delete this;
}

void VideoCapture::run()
{
    if (cap.isOpened())
    {
        while (true)
        {
            // cv::waitKey(1);
            // sleep_for(nanoseconds(500));
            usleep(50000);
            // cap >> frame;
            cap.read(frame);
            if (!frame.empty())
            {
                mPixmap = cvMatToQPixmap(frame);
                emit newPixmapCaptured();
            }
        }
    }
}

QImage VideoCapture::cvMatToQImage(const cv::Mat &inMat)
{
    // std::cout << inMat.type() << std::endl;
    switch (inMat.type())
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_ARGB32);

        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_RGB888);

        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_Grayscale8);
#else
        static QVector<QRgb> sColorTable;

        // only create our color table the first time
        if (sColorTable.isEmpty())
        {
            sColorTable.resize(256);

            for (int i = 0; i < 256; ++i)
            {
                sColorTable[i] = qRgb(i, i, i);
            }
        }

        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_Indexed8);

        image.setColorTable(sColorTable);
#endif

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

QPixmap VideoCapture::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(cvMatToQImage(inMat));
}