#include "IFVPlayer.h"
#include <thread>
#include "FFPlayer.h"

IFVPlayer::IFVPlayer()
{
}

IFVPlayer *IFVPlayer::getInstance()
{
	static IFVPlayer iffplay_;
	return &iffplay_;
}

void IFVPlayer::setSurfaceHolder(void *surfaceHolder)
{
	if (!surfaceHolder)
		return;
    mSurfaceHolder = surfaceHolder;
}

void IFVPlayer::setPlaySource(const string &url)
{
	if (url.empty())
	{
		return;
	}
    mUrl = url;
}

void IFVPlayer::play()
{
    {
		std::lock_guard<std::mutex> lock(mGuard);
		if (STATE_PAUSED == mCurrentState) {
			ffplay_play_pause();
			mCurrentState = STATE_PLAYING;
			return;
		}
    }

    if (mUrl.empty()){
        return;
    }

   {
		std::lock_guard<std::mutex> lock(mGuard);
		if (STATE_IDLE != mCurrentState)
		{
			return;
		}
		mCurrentState = STATE_PLAYING;
	}

   std::thread thd = std::thread([&]() {
        ffplay_play(mUrl.data(), (void*)mSurfaceHolder);
    });
    thd.detach();
}

void IFVPlayer::pause()
{
    ffplay_play_pause();
}

void IFVPlayer::stop()
{
	{
		std::lock_guard<std::mutex> lock(mGuard);
		if (mCurrentState == STATE_IDLE) {
			return;
		}
		mCurrentState = STATE_IDLE;
	}
    ffplay_stop();
}

void IFVPlayer::release()
{

}

void IFVPlayer::seekToTime(long msec)
{
	if (msec < 0) {
		return;
	}
	if (msec > getTotalTime()) {
		return;
	}
	std::lock_guard<std::mutex> lock(mGuard);
	if (STATE_PLAYING == mCurrentState || STATE_PAUSED == mCurrentState)
	{
		ffplay_seek(msec);
	}
}

void IFVPlayer::fastForward()
{
	std::lock_guard<std::mutex> lock(mGuard);
	if (STATE_PLAYING == mCurrentState || STATE_PAUSED == mCurrentState)
	{
		ffplay_fastForward();
	}
}

void IFVPlayer::fastBack()
{
	std::lock_guard<std::mutex> lock(mGuard);
	if (STATE_PLAYING == mCurrentState || STATE_PAUSED == mCurrentState)
	{
		ffplay_fastBack();
	}
}

long IFVPlayer::getCurrentTime()
{
	std::lock_guard<std::mutex> lock(mGuard);
	if (STATE_PLAYING == mCurrentState || STATE_PAUSED == mCurrentState)
	{
		return ffplay_get_current_time();
	}
	return -1;
}

long IFVPlayer::getTotalTime()
{
	std::lock_guard<std::mutex> lock(mGuard);
	if (STATE_PLAYING == mCurrentState || STATE_PAUSED == mCurrentState)
	{
		return ffplay_get_total_time();
	}
	return -1;
}

bool IFVPlayer::isPlaying()
{
	std::lock_guard<std::mutex> lock(mGuard);
	return STATE_PLAYING == mCurrentState;
}

void IFVPlayer::setVolume(float leftVolume, float rightVolume)
{
	std::lock_guard<std::mutex> lock(mGuard);
	if (STATE_PLAYING == mCurrentState || STATE_PAUSED == mCurrentState)
	{
		ffplay_update_volume(leftVolume, rightVolume);
	}
    
}

void IFVPlayer::setPlayerListener()
{
	 
}
