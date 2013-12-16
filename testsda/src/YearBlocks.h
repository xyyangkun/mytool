/*
 * YearBlocks.h
 *
 *  Created on: 2013-10-24
 *      Author: yangkun
 */

#ifndef YEARBLOCKS_H_
#define YEARBLOCKS_H_
#include "Blocks.h"
#include "MultBlocks.h"

namespace gtsda
{

class YearBlocks: public gtsda::MultBlocks
{
public:
	//���
	static const unsigned char year_head[8];//={0x59,0x45,0x41,0x52,0xa5,0xa5,0xa5,0xa5};

	YearBlocks(bool bIsRead=true,bool bIsWrite=true);
	virtual ~YearBlocks();
	int get_day_num()const {return yeardata->year_queue_data.queue_size;};//��ȡ��������ĸ���
	int read();
	//���룬��ȡ������
	virtual int add(const struct  seek_block &sb);
	virtual int del(const struct  seek_block &sb);
	virtual int Get   (struct  seek_block &sb,get_type get) ;
	virtual int GetHead(struct  seek_block &sb);
	virtual int GetTail(struct  seek_block &sb);
	//�ж�ʱ���seek�ǲ������������
	virtual int In(struct  seek_block &sb, InType iType=InTime);
	virtual inline long long TimeIn(int iTime);
	virtual inline int       SeekIn(long long llSeek);
private:
	struct year_block *yeardata;
	bool bIsWrite;
};

} /* namespace gtsda */
#endif /* YEARBLOCKS_H_ */
