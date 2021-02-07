#ifndef IFLYTEK_IFV_PACKET_QUEUE_I
#define IFLYTEK_IFV_PACKET_QUEUE_I
#include "playutils.h"

class CPacketQueue
{
public:
	static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block, int *serial);
	static int packet_queue_put_private(PacketQueue *q, AVPacket *pkt);
	static int packet_queue_put(PacketQueue *q, AVPacket *pkt);
	static int packet_queue_put_nullpacket(PacketQueue *q, int stream_index);
	static int packet_queue_init(PacketQueue *q);
	static void packet_queue_flush(PacketQueue *q);
	static void packet_queue_destroy(PacketQueue *q);
	static void packet_queue_abort(PacketQueue *q);
	static void packet_queue_start(PacketQueue *q);
	static AVPacket flush_pkt;
};

#endif//IFLYTEK_IFV_PACKET_QUEUE_I
