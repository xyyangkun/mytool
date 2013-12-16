/*
 * GTsource.h
 *
 *  Created on: 2013-12-9
 *      Author: yangkun
 */

#ifndef GTSOURCE_H_
#define GTSOURCE_H_

#include "FramedSource.hh"
#include "DataWR.h"



// The following class can be used to define specific encoder parameters
class GTParameters {
  //%%% TO BE WRITTEN %%%
public:
	unsigned channel;
};

class GTsource: public FramedSource {
public:
  static GTsource* createNew(UsageEnvironment& env,
				 GTParameters params);

public:
  static EventTriggerId eventTriggerId;
  // Note that this is defined here to be a static class variable, because this code is intended to illustrate how to
  // encapsulate a *single* device - not a set of devices.
  // You can, however, redefine this to be a non-static member variable.

protected:
  GTsource(UsageEnvironment& env, GTParameters params);
  // called only by createNew(), or by subclass constructors
  virtual ~GTsource();

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();
  //virtual void doStopGettingFrames(); // optional

private:
  static void deliverFrame0(void* clientData);
  void deliverFrame();

private:
  static unsigned referenceCount; // used to count how many instances of this class currently exist
  GTParameters fParams;

  gtsda::DataRead *dr;
  u_int8_t* newFrameDataStart ;
  unsigned newFrameSize ;
  bool is_over;
  unsigned left_value;
  long long fDurationtime;
};

#endif
