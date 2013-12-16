/*
 * TestInMem.cpp
 *
 *  Created on: 2013-10-28
 *      Author: yangkun
 */
#include "Test.h"
#include "../DataWR.h"
#include <fstream>
using std::iostream;
using std::ifstream;
using std::ofstream;

TestInMem::TestInMem()
	:bMarkWR(true),bIsRun(false)
{



}
int TestInMem::Init()
{
	ttt();
	int ret;
	//���
	int i=5;
start:
	try{
	yb = new YearBlocks();
	}
	catch(int err)
	{
		cout << "catch error!!\n";
		print_err(err);
		if(BLOCK_ERR_DATA_HEAD == err )
		{
			cout << " maybe this is new disk, and I will formate this disk!!!" << endl;
			format();
			ttt();
			if(!i--){
				cout << "too much wrong !! and exit " << endl;
				exit(-1);
			}
			goto start;
			cout << endl << endl;
		}else
		{
			cout << "other error and I will exit" << endl;
			//this->~TestInMem();
			exit(1);
		}
	}



	//�������
	dbbac = new DayBlocks();
	//������л�ȡ�������
	struct  seek_block sb;
	if( ( ret = yb->GetTail(sb) ) < 0)
	{
		print_err( ret );//�쳣
		//����ǿյ�
		if(BLOCK_ERR_EMPTY == ret)
		{
			sb.seek = first_block + Blocks::get_block_num(sizeof(struct year_block)) + \
					Blocks::get_block_num(sizeof(struct day_block));
			sb.time = gettime();
			if( ( ret = yb->add(sb) ) < 0 )
			{
				print_err( ret );//�쳣
				return ret;
			}
		}
		else
			return ret;
	}
	//��ȡ���
	db = new DayBlocks(sb.seek);
	ttt();
	return 0;
}

TestInMem* TestInMem::newtest()
{
	hd = new char [TestInMemSize+4];
	if( !hd )
	{
		cout << "new data err!" << endl;
	}
	ifstream fin;
	//���ļ������ڴ���
	fin.open("/tmp/TestInMem.bin");
	if(fin.fail())
	{
		cout << "open /tmp/TestInMem.bin fail" << endl;
		memset(hd, 0 ,TestInMemSize+4);
	}
	else
	{
		cout << "while read data..." << endl;
		//fin >> hd;
		fin.read(hd, TestInMemSize + 4);
	}
	publictime = *(int *)(hd + TestInMemSize);
	cout << "begine publictime = " << publictime << endl;
	return new TestInMem;
}
TestInMem::~TestInMem()
{
	*(int *)(hd + TestInMemSize) = publictime ;
	ttt();
	if(yb)
	{
		delete yb;
		yb = NULL;
	}
	if(dbbac)
	{
		ttt();
		delete dbbac;
		dbbac = NULL;
	}
	if(db)
	{
		ttt();
		delete db;
		db = NULL;
	}
	if(hd)
	{
		ttt();
		//return ;
		//���ļ�д���ڴ���
		cout << "end publictime = " << publictime << endl;
		cout << "while write in ..." << endl;
		ofstream fo("/tmp/TestInMem.bin");
		fo.write(hd, TestInMemSize + 4);
		delete [] hd;
		hd = NULL;
		cout << "write ok" << endl;
	}

}
char * TestInMem::hd=NULL;
void TestInMem::start()
{
	struct seek_block sb;//,earliest_day_block;
	int ret;
	int now,iOldTime=gettime(false);;
	bIsRun = true;
	long long seek;


	if(bMarkWR)
	{
		//������л�ȡ����
		if( (ret = db->GetTail(sb) ) != 0 )
		{
			print_err(ret);
			seek = db->GetNext();
		}
		else
			seek = sb.seek;
		cout << " current seek: " << seek << endl;
		while(bIsRun)
		{
			usleep(50);
			now = gettime();
			cout <<"\n ::" << now << endl;
			unsigned int tmp_num=0;
			while(tmp_num<20)
				tmp_num= rand() % 4000;
			tmp_num = tmp_num/4*4;
			DataRead *dr = new DataRead(tmp_num);
			hb = new SecBlocks(tmp_num +  sizeof(struct hd_frame), seek);
			hb->addonetime(*dr);
			delete dr;
			dr = NULL;

			//�жϽ����ǲ��ǹ�ȥ��
			if(now/SECOFDAY != iOldTime/SECOFDAY)
			{
				delete db;
				db = new DayBlocks(sb.seek,false);
				ret=yb->add(sb);
				print_err(ret);
				if(BLOCK_ERR_FULL == ret)
				{
					seek = first_block + Blocks::get_block_num(sizeof(struct year_block));
				}
			}
			//Ӳ���ǲ������ˣ�
			if(HdSize - seek < hb->GetBlocks())
			{
				cout << "Warning:: disk is full " << endl;
				//Ӳ�����ˣ������ֻ��һ�죬˵��Ӳ�̲�����һ�졣
				if(1==yb->get_day_num())
				{
					cout << "Warning:: capacity of disk can't save one day " << endl;
					*dbbac = *db;// warning
					seek =  first_block + Blocks::get_block_num(sizeof(struct year_block)) + \
										Blocks::get_block_num(sizeof(struct day_block)) + \
										Blocks::get_block_num(sizeof(struct day_block));
				}
				else
					seek =  first_block + Blocks::get_block_num(sizeof(struct year_block)) + \
					Blocks::get_block_num(sizeof(struct day_block));
			}
			//���Ҫ����鸲����
			yb->GetHead(sb);//��������
			if(sb.seek - seek>=0 &&\
					hb->GetBlocks()>= sb.seek - hb->GetSeek())
			{
				cout << "Warning:: the day block will be cover " << endl;
				*dbbac = *db;// warning
				delete db;
				db = NULL;
				yb->del(sb);//ɾ�����
				sb.seek = first_block + Blocks::get_block_num(sizeof(struct year_block)) + \
						Blocks::get_block_num(sizeof(struct day_block));
				sb.time = gettime(false);
				if( ( ret = yb->add(sb) ) < 0 )
				{
					print_err( ret );//�쳣

				}
				//��ȡ���
				db = new DayBlocks(sb.seek,false);
			}

			seek += hb->GetBlocks();
			sb.time = now;
			sb.seek = seek;

			//�������������
			ret = db->add(sb);
			if(ret<0  )
			{
				print_err(ret);
				if(BLOCK_ERR_DAY_SEC_MUT != ret)
					bIsRun = false;
			}

			iOldTime = now;
			delete hb;//�ͷ��ڴ�

		}
		cout << " out " <<endl;

	}
	else
	{

		cout << "haha" << endl;
	}
	bIsRun = false;
}

int TestInMem::write()
{
	ttt();
	return 0;
}

void TestInMem::format()
{
	publictime = 1;
	memset(hd, 0, TestInMemSize+4);
	//formate year block
	struct year_block *yb = (struct year_block *)(hd + first_block*BLOCKSIZE);
	memcpy(yb->year_head, YearBlocks::year_head, sizeof(YearBlocks::year_head));
	//formate day bac block
	struct day_block *dbbac = (struct day_block *)(hd + first_block*BLOCKSIZE + \
			Blocks::get_block_num(sizeof(struct YearBlocks))*BLOCKSIZE );
	memcpy(dbbac->day_head, DayBlocks::day_head, sizeof(DayBlocks::day_head));
	//formate day block
	struct day_block *db = (struct day_block *)(hd + first_block*BLOCKSIZE + \
			Blocks::get_block_num(sizeof(struct YearBlocks))*BLOCKSIZE  + \
			Blocks::get_block_num(sizeof(struct DayBlocks))*BLOCKSIZE );
	memcpy(db->day_head, DayBlocks::day_head, sizeof(DayBlocks::day_head));
}
