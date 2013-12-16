/*
 * AudioSource.h
 *
 *  Created on: 2013-12-13
 *      Author: yangkun
 */

#ifndef AUDIOSOURCE_H_
#define AUDIOSOURCE_H_
#include "FramedSource.hh"
#include "DataWR.h"
class AudioSource: public FramedSource
{
public:
	AudioSource(UsageEnvironment& env);
	virtual ~AudioSource();



	private: // redefined virtual functions:
	  virtual void doGetNextFrame();
	  virtual int readFromFile() ;
	private:
	  static void incomingDataHandler(AudioSource* source);
	  void incomingDataHandler1();

	  gtsda::DataRead *dr;
	  u_int8_t* newFrameDataStart ;
	  unsigned newFrameSize ;
	  bool is_over;
	  unsigned left_value;
	  unsigned all_value;
	  long long fDurationtime;
};

#endif /* AUDIOSOURCE_H_ */
