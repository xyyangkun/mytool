/*
 * AudioSource.cpp
 *
 *  Created on: 2013-12-13
 *      Author: yangkun
 */

#include "AudioSource.h"

AudioSource::AudioSource(UsageEnvironment& env):FramedSource(env)
{
	// TODO Auto-generated constructor stub
#include <Blocks.h>
	dr = new gtsda::DataRead(0,gtsda::block, 0x20000);
}

AudioSource::~AudioSource()
{
	delete dr;
	// TODO Auto-generated destructor stub
}
void AudioSource::doGetNextFrame()
{
	incomingDataHandler(this);
}
int AudioSource::readFromFile()
{

}
void AudioSource::incomingDataHandler(AudioSource* source)
{
	  source->incomingDataHandler1();
}
void AudioSource::incomingDataHandler1()
{
	//if (!isCurrentlyAwaitingData()) return; // we're not ready for the data yet

	all_value =0;
	std::cout << " debug !!!! fMaxSize: "<<fMaxSize << std::endl;




		dr->readpool();
		newFrameDataStart = (u_int8_t*)( dr->get_the_frame_buffer()->frame_buf); //%%% TO BE WRITTEN %%%
		newFrameSize =  dr->get_frame_buff_size(); //%%% TO BE WRITTEN %%%


		// Deliver the data here:
		if (newFrameSize > fMaxSize) {
		fFrameSize = fMaxSize;
		fNumTruncatedBytes = newFrameSize - fMaxSize;
		} else {
		fFrameSize = newFrameSize;
		}



#if 0
		if( 0 == fPresentationTime.tv_sec&&0==fPresentationTime.tv_usec)
		{
			std::cout << "debug1!!" << std::endl;
			gettimeofday(&fPresentationTime, NULL); // If you have a more accurate time - e.g., from an encoder - then use that instead.
			fDurationtime = fPresentationTime.tv_usec + fPresentationTime.tv_sec*1000000;
			fDurationInMicroseconds = 20000;
		}
		else
		{
			//std::cout << "debug2!!" << std::endl;
			//fDurationInMicroseconds = fDurationInMicroseconds + 40000;
			fDurationInMicroseconds = 20000;
			fDurationtime +=  20000;
			fPresentationTime.tv_sec  = fDurationtime / 1000000;
			fPresentationTime.tv_usec = fDurationtime % 1000000;
		}
#else
		fDurationInMicroseconds = 20000;
		gettimeofday(&fPresentationTime, NULL); // If you have a more accurate time - e.g., from an encoder - then use that instead.
#endif

	// If the device is *not* a 'live source' (e.g., it comes instead from a file or buffer), then set "fDurationInMicroseconds" here.
	memmove(fTo, newFrameDataStart, fFrameSize);

	// After delivering the data, inform the reader that it is now available:
	FramedSource::afterGetting(this);
}
