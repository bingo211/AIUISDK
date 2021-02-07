#ifndef IFVPLAYER_H
#define IFVPLAYER_H
#include <string>
#include <mutex>
using namespace std;
#define SurfaceHolder void*

enum :int{
    STATE_IDLE = 0,
    STATE_ERROR,
    STATE_PREPARING,
    STATE_PREPARED,
    STATE_PAUSED,
	STATE_PLAYING,
    STATE_COMPLETED
};

class IFVPlayer
{
public:
    IFVPlayer();
    static IFVPlayer *getInstance();
    
   ///////////////////////////////////public Method////////////////////////////////////////////////////////
    /**
     * Sets the {@link SurfaceHolder} to use for displaying the video
     * portion of the media.
     *
     * @param surfaceHolder the SurfaceHolder to use for video display
     * @throws Exception if IFVPlayer is not initialized,
     *                   if surfaceHolder is null.
     */
    void setSurfaceHolder(SurfaceHolder surfaceHolder);

    /**
     * Sets the data source (file-path or http/rtsp URL) to use.
     *
     * @param url the path of the file, or the http/rtsp URL of the stream you want to play
     * @throws Exception if IFVPlayer is not initialized,
     *                   if url is null or empty;
     *                   if it is called in an invalid state.
     */
    void setPlaySource(const std::string& url);

    /**
     * Starts or resumes playback. If playback had previously been paused,
     * playback will continue from where it was paused. If playback had
     * been stopped, or never started before, playback will start at the
     * beginning.
     *
     * @throws Exception if IFVPlayer is not initialized,
     *                   if it is called in an invalid state.
     */
    void play();
     /**
     * Pauses playback. Call start() to resume.
     *
     * @throws Exception if IFVPlayer is not initialized,
     *                   if it is called in an invalid state.
     */
    void pause();

    /**
     * Stops playback after playback has been stopped or paused.
     *
     * @throws Exception if IFVPlayer is not initialized,
     *                   if it is called in an invalid state.
     */
    void stop();

    /**
     * Releases resources associated with this ifvPlayer object
     *
     * @throws Exception if IFVPlayer is not initialized,
     *                   if it is called in an invalid state.
     */
    void release();

    /**
     * Seeks to specified time position.
     *
     * @param msec the offset in milliseconds from the start to seek to
     * @throws Exception if IFVPlayer is not initialized,
     *                   if the msec less than 0,
     *                   if the msec larger than totalTime.
     */
    void seekToTime(long msec);

    /**
     * Fast forward play,
     * progress increased by 1500 milliseconds until maximum totalTime
     *
     * @throws Exception if IFVPlayer is not initialized.
     */
    void fastForward();

    /**
     * Fast backward play
     * progress reduced by 1500 milliseconds until minimum 0
     *
     * @throws Exception if IFVPlayer is not initialized.
     */
    void fastBack();

    /**
     * Gets the current playback position.
     *
     * @return the current position in milliseconds
     */
    long getCurrentTime();

    /**
     * Gets the duration of the file.
     *
     * @return the duration in milliseconds, if no duration is available
     * (for example, if streaming live content), -1 is returned.
     */
    long getTotalTime();

    /**
     * Checks whether the MediaPlayer is playing.
     *
     * @return true if currently playing, false otherwise
     */
    bool isPlaying();

    /**
     * Sets the volume on this player.
     *
     * @param leftVolume  left volume scalar
     * @param rightVolume right volume scalar
     * @throws Exception if IFVPlayer is not initialized.
     */
    void setVolume(float leftVolume, float rightVolume);

     /**
     * Gets the IFVPlayer play state.
     *
     * @return ifvpalyer palying state
     * -1 : STATE_ERROR
     * 0 : STATE_IDLE
     * 1 : STATE_ERROR
     * 2 : STATE_PREPARING
     * 3 : STATE_PREPARED
     * 4 : STATE_PAUSED
     * 5 : STATE_COMPLETED
     */
    int getPlayStatus(){
        return mCurrentState;
    }
private:
	void setPlayerListener();
private:
    std::string mUrl;
    SurfaceHolder mSurfaceHolder;
	int mCurrentState{ STATE_IDLE };
	std::mutex mGuard;
};

#endif // IFVPLAYER_H
