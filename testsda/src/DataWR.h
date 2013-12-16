/*
 * DataWR.h
 *
 *  Created on: 2013-10-29
 *      Author: yangkun
 */

#ifndef DATAWR_H_
#define DATAWR_H_
//���ݵĻ�ȡ��д��
#include "Blocks.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "media_api.h"
#ifdef __cplusplus
}
#endif
namespace gtsda
{
class DataRead;
struct bblock
{
	unsigned int size;//p���ж��xxd��ֵ
	unsigned int xxd;
	unsigned char p[4];
};
extern int publictime;
int gettime(bool add = true);
class DataWrite:public gtsda::Blocks
{
public:
	DataWrite();
	DataWrite(DataWrite &a):Blocks(BUFSIZE,0,block){cout << "warning !!!!" << endl;};
	virtual ~DataWrite();
	int writedata();
	DataWrite  &operator=( DataRead &dr);
	int getdata(DataRead &dr);
	int getdata(const char *buf, unsigned int buffsize);
	unsigned int  get_frame_buff_size(){return buffsize;};
	//char *   GetBuf()  {return buf;};
private:
	char *buf;
	long buffsize;
	int fifo_init();
	int fifo_write(const char *buf, int size);
	int fd;
};


#ifndef MEMIN
#define MEDIA_VIDEO		0x01		//��Ƶ����
#define MEDIA_AUDIO	0x02		//��Ƶ����

struct NCHUNK_HDR {	//avi��ʽ�����ݿ�ͷ��־�ṹ
#define IDX1_VID  		0x63643030	//AVI����Ƶ�����
#define IDX1_AID  		0x62773130	//AVI����Ƶ���ı��
	unsigned long  chk_id;
	unsigned long  chk_siz;
};
typedef struct{
    ///ѹ�������Ƶ֡
    ///ʹ������ṹʱҪ�ȷ���һ���󻺳���,Ȼ�󽫱��ṹ��ָ��ָ�򻺳���

#define MEDIA_VIDEO		0x01		//��Ƶ����
#define MEDIA_AUDIO	0x02		//��Ƶ����

#define FRAMETYPE_I		0x0		// frame flag - I Frame
#define FRAMETYPE_P		0x1		// frame flag - P Frame
#define FRAMETYPE_B		0x2
#define FRAMETYPE_PCM	0x5		// frame flag - Audio Frame

	struct timeval           tv;			   ///<���ݲ���ʱ��ʱ���
	unsigned long	           channel;	          ///<ѹ��ͨ��
	unsigned short           media;		   ///<media type ��Ƶ����Ƶ
	unsigned short           type;		          ///<frame type	I/P/����...
	long                          len;	                 ///<frame_buf�е���Ч�ֽ���
	struct NCHUNK_HDR chunk;                ///<���ݿ�ͷ��־��Ŀǰʹ��avi��ʽ
	unsigned char            frame_buf[4];    ///<��ű�������Ƶ���ݵ���ʼ��ַ
}enc_frame_t;

#endif
class DataRead: public gtsda::Blocks
{
public:
#ifdef MEMIN
	DataRead(unsigned int uBufSize,long long llSeek=0,blocktype bt=block);
	DataRead(DataRead &a):Blocks(a.GetSize(),a.GetSeek(),a.GetType()){cout << "warning !!!!" << endl;};
#else
	DataRead(long long llSeek=0,blocktype bt=block,unsigned int channel = 0);
	//DataRead(unsigned int channel );
#endif
	virtual ~DataRead();
	int readpool();
	enc_frame_t* get_the_frame_buffer(){return the_frame_buffer;};
	unsigned int  get_frame_buff_size(){return buffsize;};
	bool get_isi(){return bIsI;};
private:
#ifndef MEMIN
	media_source_t media;
	int		seq;                 ///<ý���������
	int flag;
	enc_frame_t* the_frame_buffer;
	bool bIsI; //�ǲ���I֡
	void init_pool(unsigned int channel);
	long buffsize;
#endif

	bblock *bs;
};
} /* namespace gtsda */
#endif /* DATAWR_H_ */
