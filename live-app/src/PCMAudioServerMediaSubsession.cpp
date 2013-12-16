/*
 * PCMAudioServerMediaSubsession.cpp
 *
 *  Created on: 2013-12-13
 *      Author: yangkun
 */

#include "PCMAudioServerMediaSubsession.h"
#include "SimpleRTPSink.hh"
#include "AudioSource.h"
PCMAudioServerMediaSubsession*
PCMAudioServerMediaSubsession::createNew(UsageEnvironment& env, int channel)
{
	  return new PCMAudioServerMediaSubsession(env, 0x2000+channel);
}
PCMAudioServerMediaSubsession::PCMAudioServerMediaSubsession(UsageEnvironment& env, int channel)
:OnDemandServerMediaSubsession(env, True /*reuse the first source*/)
{
	// TODO Auto-generated constructor stub

}

PCMAudioServerMediaSubsession::~PCMAudioServerMediaSubsession()
{
	// TODO Auto-generated destructor stub
}
FramedSource* PCMAudioServerMediaSubsession::createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate)
{
#if 1
	return new AudioSource(envir());
#else
	GTParameters tmp;
	tmp.channel = 0x20000;
	return GTsource::createNew(envir(), tmp);
#endif
}
RTPSink* PCMAudioServerMediaSubsession::createNewRTPSink(Groupsock* rtpGroupsock,
                                  unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource)
{
	unsigned audioSamplingFrequency = 8000;
	unsigned audioNumChannels = 1;
	return SimpleRTPSink::createNew(envir(), rtpGroupsock, /*96*/0,
						 audioSamplingFrequency, "audio", "PCMU", audioNumChannels);
}
