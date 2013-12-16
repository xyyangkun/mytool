/*
 * err.h
 *
 *  Created on: 2013-10-28
 *      Author: yangkun
 */

#ifndef ERR_H_
#define ERR_H_
#include <iostream>
using std::cout;
using std::endl;
namespace gtsda
{
#define UNKNOW_ERR 				-1
#define BLOCK_ERR_DATA_HEAD 	-2 		//�����,���,��������ݣ����ݿ�ͷ����
#define HD_ERR_READ				-3 		//Ӳ�̶�����
#define HD_ERR_WRITE			-4 		//Ӳ�̶�����
#define BLOCK_ERR_NULL 			-5		//����ָ�����ΪNULL
#define BLOCK_ERR_ZERO 			-6		//����ָ�������Ч����������ȫΪ0
#define BLOCK_ERR_FULL 			-7 		//�������������ݣ�����д���ˣ�Ӧ��ֻ������д��
#define BLOCK_ERR_EMPTY 		-8		//�������������ݣ�Ϊ�գ�û����Ч����
#define BLOCK_ERR_NOT_IN    	-9 		//ʱ�䣬seek������飬��飬�����
#define BLOCK_ERR_NOT_ENOUGH	-10		//���ƿ�ʱ��Ŀ�ĵ�ַû���㹻���ڴ档
#define BLOCK_ERR_DAY_SEC_MUT 	-11		//�����һ������λ���ж������Ӧ���п��ܵ������1��һ���ж��I֡2��ϵͳʱ�������ǰ����
#define HD_ERR_OVER				-12

extern const  char *cErr[];
#define  print_err( iNo) \
{ \
	if(iNo<0){ \
	cout << endl << "error: " << cErr[abs(iNo)-1] ; \
	cout << "\t"<< __FILE__ << "\t" << __FUNCTION__ << "\t" << __LINE__ << endl; \
	}\
}while(0)
#define ttt() 	cout << __FILE__ << "\t" << __FUNCTION__ << "\t" << __LINE__ << endl;
int myprint(const unsigned char *p, long size);

#define LOCKFILE "/var/run/mydaemon.pid"
#define LOCKREAD "/var/run/sdaread.pid"
#define LOCKWRITE "/var/run/sdawrite.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
int already_running(const char *filename);
} /* namespace gtsda */
#endif /* ERR_H_ */
