#ifndef CAIUIPLAYER_H
#define CAIUIPLAYER_H
#include "IFVPlayer.h"

/**
 * @brief AIUIPlayer_play 音乐播放
 * @param mp3 mp3网络地址
 */
void AIUIPlayer_play(const std::string& mp3)
{
    //销毁播放器
    IFVPlayer::getInstance()->stop();
    IFVPlayer::getInstance()->setPlaySource(mp3);
    IFVPlayer::getInstance()->play();
}

/**
 * @brief AIUIPlayer_pause  音乐暂停和继续
 */
void AIUIPlayer_pause()
{
    IFVPlayer::getInstance()->pause();
}

/**
 * @brief AIUIPlayer_destroy   播放器销毁
 */
void AIUIPlayer_destroy()
{
    IFVPlayer::getInstance()->stop();
}

#endif // CAIUIPLAYER_H
