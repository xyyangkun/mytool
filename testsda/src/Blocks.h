/*
 * Blocks.h
 *
 *  Created on: 2013-10-24
 *      Author: yangkun
 */

#ifndef BLOCKS_H_
#define BLOCKS_H_
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

#include "gtlog.h"
#include <error.h>

#include "hdwr.h"
#include "err.h"

#define CRC

using std::cout;
using std::endl;
using std::ostream;
using std::istream;
namespace gtsda
{



/*Ӳ��Ĭ�Ͽ��С512�ֽ�  ���ֵ����˵�ǲ��ܸĵ�*/
#define BLOCKSIZE 512
#define BUFSIZE  400*1024
/*����������ܹ���800��*/
#define MAXDAY 800
/*��ѭ��������ͷ��ƫ��*/
#define YEAR_OFFSET 8
#define SECOFDAY (24*3600)
#define first_block 1
//#define get_block_num(buffsize) (( (buffsize) + BLOCKSIZE -1)/BLOCKSIZE )
typedef enum
{
	noblock		= 0, /*ʲô��Ҳû��*/
	block		= 1,
	collection	= 2,/*���������İ�*/
	year		= 3,
	day			= 4,
	day_bac		= 5,
	sec			= 6,
	audio		= 7,

}blocktype;
typedef enum
{
	get_start = 1,
	get_tail   = 2
}get_type;
struct  seek_block{ int time; long long seek;}__attribute__ ((packed));
struct year_queue{ unsigned int queue_size ,queue_head,queue_tail;};
struct year_block
{
	unsigned char year_head[8];
	struct year_queue year_queue_data;
	struct seek_block seek_block_data[MAXDAY];
}__attribute__ ((packed));
//struct day_queue { int index, size;};
struct day_block
{
	unsigned char day_head[8];
//	struct day_queue day_queue_data;
	struct seek_block seek_block_data[SECOFDAY];
}__attribute__ ((packed));

struct hd_frame
{
	char data_head[8];			/*֡����ͷ�ı�־λ 0x5345434fa55a5aa5*/
	short frontIframe;			/*ǰһ��I֡����ڱ�֡��ƫ�Ƶ�ַ   ���ǰһ֡��Ӳ�̵�����棬���ֵ�����Ǹ�ֵ*/
	short is_I;		/*��֡�ǲ���I֡*/
	unsigned int size;			/*��֡��Ƶ���ݿ�Ĵ�С*/
	unsigned int crc;			//����λ
}__attribute__ ((packed));
class Blocks
{
public:
	Blocks(unsigned int uBufSize,long long llSeek=0,blocktype bt=block);
	Blocks(char *buf,unsigned int uSizeOfBuf,unsigned int uBufSize,long long llSeek=0,blocktype bt=block);
	Blocks(long long llSeek,unsigned int uBufSize);//read from disk��and get type
	unsigned int GetSize(){return uSize;};
	long long GetSeek(){return llSeek;};
	void SetSeek(long long llSeek)
	{
		if(llSeek<0)
		{
			cout << "set seek error" << endl;
			throw -1;
		}
		else
			this->llSeek=llSeek;

	};
	long long GetBlocks(){return uNumOfBlocks;};
	long long GetNext(){return llSeek + uNumOfBlocks;};//��һ��д���λ�ã����Ǳ������һ��
	virtual ~Blocks();
	blocktype GetType()const{return bType;};
	const void * const GetBuf()const  {return cBuff;};
	void SetBuf(char *buf,unsigned int uSizeOfBuf)
	{
		memcpy(this->cBuff, buf, (uSize<uSizeOfBuf?uSize:uSizeOfBuf));
	};
	static unsigned int get_block_num(unsigned int  buffsize){ \
		return (( (buffsize) + BLOCKSIZE -1)/BLOCKSIZE ); }
	static blocktype judge_type(const char *buf);
	friend ostream & operator <<(ostream &os,const Blocks &bk);

	int read();
	int write();
	Blocks & operator=(const Blocks &bs);
private:
	Blocks(Blocks &bk){};//��ʱ��ֹ���ƶ��󣡣�����
	char *cBuff;
	blocktype bType;
	unsigned int uSize;			//�������ܴ�С
	unsigned int uNumOfBlocks;	//buf��ռ�Ŀ顣
	long long llSeek;			//�ڶ��ٿ�
	static pthread_mutex_t mutex_wr;
};

} /* namespace gtsda */
#endif /* BLOCKS_H_ */
