#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QSlider>
#include <QToolBar>
#include <QAudioOutput>
#include <string>

class VideoPlayer
{

public:
    VideoPlayer(QString filePath, int width, int height);
    ~VideoPlayer();

    /**
     * @brief This function triggers the media player to begin playing the video.
     */
    void playVideo();

private:
    // Each group of components needed for the player are initialized in a separate function

    /**
     * @brief Initializes the main window object that will contain the video player
     *
     * @param title The title of the window that will contain the video player
     * @return void
     */
    void initWindow(QString title);

    /**
     * @brief Initializes the media player, video widget, and audio output
     *
     */
    void initPlayer();

    /**
     * @brief Initializes play/pause buttons
     *
     */
    void initBtns();

    /**
     * @brief Initializes the progress slider
     *
     */
    void initSlider();

    /**
     * @brief Initializes the toolbar containing play buttons and slider
     *
     */
    void initToolbar();

    /**
     * @brief Initializes all emit-slot connections to allow play/pause buttons and slider to control the media player
     *
     */
    void initConnections();

    int width;
    int height;

    QString filePath;

    QMainWindow window;

    QMediaPlayer *player;
    QVideoWidget *vidWidget;
    QAudioOutput *audioOutput;

    QPushButton *playButton;
    QPushButton *pauseButton;

    QSlider *slider;

    QToolBar *toolBar;
};

#endif // VIDEOPLAYER_H
