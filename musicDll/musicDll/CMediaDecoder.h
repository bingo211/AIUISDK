#ifndef IFLYTEK_IFV_MEDIA_DECODER_I
#define IFLYTEK_IFV_MEDIA_DECODER_I

#include "playutils.h"

class CMediaDecoder
{
public:
	static int decoder_start(Decoder *d, int(*fn)(void *), const char *thread_name, void* arg);
	static void decoder_init(Decoder *d, AVCodecContext *avctx, PacketQueue *queue, SDL_cond *empty_queue_cond);
	static int decoder_decode_frame(Decoder *d, AVFrame *frame, AVSubtitle *sub);
	static void decoder_destroy(Decoder *d);
	static void decoder_abort(Decoder *d, FrameQueue *fq);
	static int decoder_reorder_pts;
};

#endif//IFLYTEK_IFV_MEDIA_DECODER_I
