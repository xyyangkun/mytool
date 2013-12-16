/*
 * YearBlocks.cpp
 *
 *  Created on: 2013-10-24
 *      Author: yangkun
 */

#include "YearBlocks.h"
#include "err.h"
namespace gtsda
{
const unsigned char YearBlocks::year_head[8]={0x59,0x45,0x41,0x52,0xa5,0xa5,0xa5,0xa5};
YearBlocks::YearBlocks(bool bIsRead, bool bIsWrite)
	:MultBlocks( (get_block_num(sizeof(struct year_block)) *BLOCKSIZE) ,first_block,year),\
	 bIsWrite(bIsWrite)
{
	int ret;
	yeardata = (struct year_block *)GetBuf();
	//��Ӳ���ж�ȡ���
	if(bIsRead)
	{
		if( ( ret=read() ) < 0)
		{
	#if 0
			if( BLOCK_ERR_DATA_HEAD == ret )
			{
				print_err( ret);
			}
			else
				print_err( UNKNOW_ERR);
			memset(yeardata, 0 ,GetSize());
			memcpy(yeardata->year_head, year_head, sizeof(year_head));	//�����ļ�ͷ
	#else
			throw ret;
	#endif
			//д������
			write();
		}
	}
}

YearBlocks::~YearBlocks()
{
	ttt();
	if(bIsWrite)
		write();
}

int YearBlocks::read()
{
	int ret;
	if( ( ret = Blocks::read() ) < 0 )
	{
		return ret;
	}
	const char *p =(const char *)GetBuf();
	if( memcmp(year_head,p,  sizeof(year_head)) != 0 )
	{
		print_err(BLOCK_ERR_DATA_HEAD);
		return BLOCK_ERR_DATA_HEAD;
	}
	return 0;
}


//���룬��ȡ������
int YearBlocks::add(const struct  seek_block &sb)
{
	if( &sb == NULL )
			return BLOCK_ERR_NULL;
	if( sb.time==0 || sb.seek==0)
			return BLOCK_ERR_ZERO;
	//�ж϶������Ƿ��пռ�
	if(yeardata->year_queue_data.queue_tail+1 == yeardata->year_queue_data.queue_head)
	{
		cout << "year block full\n" ;
		return BLOCK_ERR_FULL;//����
	}
	memcpy( &(yeardata->seek_block_data[yeardata->year_queue_data.queue_tail]) ,\
			&sb, sizeof(struct seek_block));
	yeardata->year_queue_data.queue_tail = (yeardata->year_queue_data.queue_tail+1)%MAXDAY;
	yeardata->year_queue_data.queue_size++;
	//д������
	if(write() < 0)
	{
		cout << "hd_write error\n";
		return HD_ERR_WRITE;
	}
	return 0;
}
//ɾ���������
int YearBlocks::del(const struct  seek_block &sb)
{
	if(yeardata->year_queue_data.queue_tail == yeardata->year_queue_data.queue_head)
	{
		cout << "emputy\n" ;
		return BLOCK_ERR_EMPTY;//����
	}
	memset( &yeardata->seek_block_data[yeardata->year_queue_data.queue_head],0 ,sizeof(struct  seek_block) );
	yeardata->year_queue_data.queue_head = (yeardata->year_queue_data.queue_head+1)%MAXDAY;
	yeardata->year_queue_data.queue_size--;
	//д������
	if(write() < 0)
	{
		cout << "hd_write error\n";
		return HD_ERR_WRITE;
	}
	return 0;
}
int YearBlocks::Get   (struct  seek_block &sb,get_type get)
{

	if(get == get_start)
		GetHead(sb);
	else
		GetTail(sb);
	return 0;
}
int YearBlocks::GetHead(struct  seek_block &sb)
{
	//block�������Ƿ�Ϸ�
	if( &sb == NULL )
		return BLOCK_ERR_NULL;
	//�ж�������ǲ��ǿյ�
	if(yeardata->year_queue_data.queue_size==0)return BLOCK_ERR_EMPTY;
	memcpy(&sb, &(yeardata->seek_block_data[yeardata->year_queue_data.queue_head]),\
						sizeof(struct seek_block));
	return 0;
}
int YearBlocks::GetTail(struct  seek_block &sb)
{
	//block�������Ƿ�Ϸ�
	if( &sb == NULL )
		return BLOCK_ERR_NULL;
	//�ж�������ǲ��ǿյ�
	if(yeardata->year_queue_data.queue_size==0)return BLOCK_ERR_EMPTY;
	memcpy(&sb, &(yeardata->seek_block_data[yeardata->year_queue_data.queue_tail-1]) ,\
				sizeof(struct seek_block));
	return 0;
}
//�ж�ʱ���seek�ǲ������������
int YearBlocks::In(struct  seek_block &sb, InType iType)
{
	if(InTime == iType)
	{
		return TimeIn(sb.time);
	}
	else
	{
		return SeekIn(sb.seek);
	}
	return UNKNOW_ERR;
}
inline long long YearBlocks::TimeIn(int iTime)
{
	unsigned int day;
	for (day = yeardata->year_queue_data.queue_head;
			day < yeardata->year_queue_data.queue_head + yeardata->year_queue_data.queue_size;
			day++)
	{
		//cout << "debug " << day - yeardata->year_queue_data.queue_head+1\
				<< " time: " << yeardata->seek_block_data[day].time << endl;
		if (yeardata->seek_block_data[day].time / SECOFDAY
				== iTime / SECOFDAY) //ʱ���������
			return yeardata->seek_block_data[day].seek;
	}
	return BLOCK_ERR_NOT_IN;
}
int YearBlocks::SeekIn(long long llSeek)
{

	unsigned int day;
	for (day = yeardata->year_queue_data.queue_head;
			day < yeardata->year_queue_data.queue_head + yeardata->year_queue_data.queue_size;
			day++)
	{
		if (yeardata->seek_block_data[day].seek
				== llSeek) //ʱ���������
			return yeardata->seek_block_data[day].time;
	}
	return BLOCK_ERR_NOT_IN;
}



} /* namespace gtsda */
