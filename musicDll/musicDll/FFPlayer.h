#ifndef IFLYTEK_FFPLAY_INCLUDE
#define IFLYTEK_FFPLAY_INCLUDE
#include <windows.h>
#include <stdint.h>
	void ffplay_play_pause();
	//Send Command "Seek"
	void ffplay_seek(uint64_t mesc);
	//Send Command "AspectRatio",example 4:3  num=4,den=3
	void ffplay_aspectratio(int num, int den);
	//Send Command "WindowSize"
	void ffplay_size(int percentage);
	//Send Command "Audio Display Mode"
	void ffplay_audio_display(int mode);
	//Send Command "Quit"
    void ffplay_stop();
	//Main function
	int ffplay_play(const char* infilename,void* winId);
	//Seek Bar
	void ffplay_seek_bar(int pos);
	//update volume
	void ffplay_update_volume(uint32_t leftVolume, uint32_t rightVolume);
	/**sss
	 * Gets the duration of the file.
	 *
	 * @return the duration in milliseconds, if no duration is available
	 * (for example, if streaming live content), -1 is returned.
	 */
	uint64_t ffplay_get_total_time();
	/**
	 * Gets the current playback position.
	 *
	 * @return the current position in milliseconds
	 */
	uint64_t ffplay_get_current_time();
	/**
	 * Fast forward play,
	 * progress increased by 1500 milliseconds until maximum totalTime
	 *
	 * @throws Exception if IFVPlayer is not initialized.
	 */
	void ffplay_fastForward();
	/**
	 * Fast backward play
	 * progress reduced by 1500 milliseconds until minimum 0
	 *
	 * @throws Exception if IFVPlayer is not initialized.
	 */
	void ffplay_fastBack();

#endif//IFLYTEK_FFPLAY_INCLUDE
