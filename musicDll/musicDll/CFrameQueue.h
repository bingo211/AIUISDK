#ifndef IFLYTEK_IFV_FRAME_QUEUE_I
#define IFLYTEK_IFV_FRAME_QUEUE_I

#include "playutils.h"
class CFrameQueue
{
public:
	static void frame_queue_unref_item(Frame *vp);
	static int frame_queue_init(FrameQueue *f, PacketQueue *pktq, int max_size, int keep_last);
	static void frame_queue_destory(FrameQueue *f);
	static void frame_queue_signal(FrameQueue *f);
	static Frame *frame_queue_peek(FrameQueue *f);
	static Frame *frame_queue_peek_next(FrameQueue *f);
	static Frame *frame_queue_peek_last(FrameQueue *f);
	static Frame *frame_queue_peek_writable(FrameQueue *f);
	static Frame *frame_queue_peek_readable(FrameQueue *f);
	static void frame_queue_push(FrameQueue *f);
	static void frame_queue_next(FrameQueue *f);
	static int frame_queue_nb_remaining(FrameQueue *f);
	static int64_t frame_queue_last_pos(FrameQueue *f);
};

#endif//IFLYTEK_IFV_FRAME_QUEUE_I
