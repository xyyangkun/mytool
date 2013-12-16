/*
gtlog��:

˵��:

	����˳����error>warn>info>dbg
	�������Ҫ�п��ؿ���
	��ʽ����ʱ��ֻ���info�����ϼ������־

P.S.
	��vmmain����������ҲҪ�����ĸ�������м�¼,����ʱ��gtlogϵ�к���
	������־����ǰ�ӱ��
*/

#ifndef GT_LOG_H
#define GT_LOG_H
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _WIN32
#include <syslog.h>
#else
#define __inline__ __inline
#endif
//����־
#ifndef _WIN32
	#define gtopenlog(name) openlog(name,LOG_CONS|LOG_NDELAY|LOG_PID,LOG_LOCAL0 );//LOG_USER);
#else
	#define gtopenlog(name)
#endif
/**********************************************************************************
 *      ������: log_headstring()
 *      ����:   ������ͷ��־��Ϣ���ɱ��������Ϣ��¼����־�ļ�
 *      ����:   head_str:ͷ������Ϣ�ַ���,��"[debug]"
 *				format:������ʽ��ͬprintf��
 *      ����ֵ: 
 *		 ע���ַ������ܳ��Ȳ�Ҫ����450�ֽ�
 *			  ʹ�ñ�����Ҫ����gtlog��
 *	Ӧ�ó���Ӧ�ò���ֱ��ʹ�ô˺���
 **********************************************************************************/
int log_headstring(const char *head_str,const char *format,...);


/*	ʹ��ʱͬprintf,��������־����֮ǰ����[ERR]���
	Ӧ�þ���:������ʱ
*/
//int gtlogerror(const char *format,...);
#ifdef _WIN32
#define gtlogerr printf
#else
#define gtlogerr(args...)  log_headstring("[ERR]",##args)
#endif
/*	ʹ��ʱͬprintf,��������־����֮ǰ����[WARN]���
  	Ӧ�þ���:��ĳ��������Ҫ��������������Ϊȱʡֵʱ*/
//int gtlogwarn(const char *format,...);
#ifdef _WIN32
#define gtlogwarn printf
#else
#define gtlogwarn(args...) log_headstring("[WARN]",##args)
#endif
/*	ʹ��ʱͬprintf,
	Ӧ�þ���:��ʼ���⺯��ʱ;��¼��xvs��������Ϣ
*/
//int gtloginfo(const char *format,...);
#ifdef _WIN32
#define gtloginfo printf
#else
#define gtloginfo(args...) log_headstring(NULL,##args) 
#endif
#define gtlogfault gtlogerr

/*	ʹ��ʱͬprintf,��������־����֮ǰ����[DBG]���
	Ӧ�þ���:��¼�����׽ӿ�ʱ�Ĳ�����Ϣ(���ڵ���xvslib��)
*/
#ifdef _WIN32
#define gtlogdebug printf
#else
#define gtlogdebug(args...) log_headstring("[DBG]",##args)
#endif

#ifdef __cplusplus
	}
#endif

#endif


