#include "dialog.h"

#include <QApplication>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QFileDialog>
#include <QAudioOutput>
#include <QIODevice>
#include <QBuffer>
#include <QMainWindow>
#include <QSlider>
#include <QPushButton>
#include <QToolBar>
#include "VideoPlayer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Get the filepath from a file dialog widow
    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Please Choose a Video",
        ".",
        "mp4 (*.mp4)"); // Accepted file formats are mp4 but can be set to additional formats as needed

    if (filePath.isNull())
        return 0;

    VideoPlayer player{filePath, 810, 500};
    player.playVideo();

    return QApplication::exec();
}
