#include "VideoPlayer.h"
#include <string>

VideoPlayer::VideoPlayer(QString _filePath, int _width, int _height)
    : filePath{_filePath}, width{_width}, height{_height}, player{new QMediaPlayer}, vidWidget{new QVideoWidget}, audioOutput{new QAudioOutput}
{

    toolBar = new QToolBar(&window);
    slider = new QSlider(Qt::Horizontal, &window);
    playButton = new QPushButton("Play", &window);
    pauseButton = new QPushButton("Pause", &window);

    initWindow("Video Player");

    initPlayer();

    initSlider();

    initToolbar();

    initConnections();
}

VideoPlayer::~VideoPlayer()
{
    delete player;
    delete vidWidget;
    delete audioOutput;
    delete playButton;
    delete pauseButton;
    delete slider;
    delete toolBar;
}

void VideoPlayer::playVideo()
{
    player->play();
}

void VideoPlayer::initWindow(QString title)
{
    window.setWindowTitle(title);
    window.resize(width, height);
    window.addToolBar(Qt::BottomToolBarArea, toolBar);
    window.setCentralWidget(vidWidget);
    window.show();
}

void VideoPlayer::initPlayer()
{
    vidWidget->setGeometry(100, 100, width, height);
    vidWidget->show();

    player->setSource(QUrl(filePath));
    player->setVideoOutput(vidWidget);
    player->setAudioOutput(audioOutput);
}

void VideoPlayer::initSlider()
{
    slider->setRange(0, player->duration() / 1000);
}

void VideoPlayer::initToolbar()
{
    toolBar->addWidget(playButton);
    toolBar->addWidget(pauseButton);
    toolBar->addWidget(slider);
}

void VideoPlayer::initConnections()
{
    // Connect play/pause button click signal to media player's play/pause slots
    QObject::connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    QObject::connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);

    // Connect slider's slider moved signal to media player's setPosition slot
    // Moves the media player's current playback position accordingly when the user drags the slider
    QObject::connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);

    // Connect the player's position changed signal to slider's setValue slot
    // Moves the slider's position as the video plays to represent video progress
    QObject::connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);

    // Connect the player's duration changed signal to slider's setMaximum slot
    // Adjust's the slider's maximum value after the video is fully loaded and the duration is known
    QObject::connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);

    // Connect the player's mediaStatusChanged signal to a lambda callback acting on the slider
    // When the player reaches the end of the video, slider should go back to its position at value = 0
    QObject::connect(this->player, &QMediaPlayer::mediaStatusChanged, this->slider, [this]()
                     {
        if (this->player->mediaStatus() == QMediaPlayer::EndOfMedia) {
            this->slider->setValue(0);
                } });

    // Connect the player's mediaStatusChanged signal to a lambda callback acting on the window
    // When the media player is closed/stopped, window should also be closed to allow the program to terminate
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged, [this]()
                     {
        if (this->player->mediaStatus() == QMediaPlayer::StoppedState) {
            this->window.close();
        } });
}
