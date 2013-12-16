CROSS_COMPILE?=		arm-hisiv200-linux-

CXX = $(CROSS_COMPILE)g++
CC =  $(CROSS_COMPILE)gcc

 
 
TOP = $(PWD)
vpath %.cpp $(TOP)/src
vpath %.o $(TOP)/OUT $(TOP)/SRC

CXXFLAGS=-g
INCLUDES = -I$(live555top)/UsageEnvironment/include -I$(live555top)/groupsock/include -I$(live555top)/liveMedia/include -I$(live555top)/BasicUsageEnvironment/include
#Ó²ÅÌ¿â
INCLUDES += -I /workplace/mywork/svn/GTIP-E_studio/src/testsda/src
INCLUDES += -I /workplace/mywork/svn/GTIP-E_studio/src/testsda/extern_src/include
CXXFLAGS += -L/workplace/mywork/svn/GTIP-E_studio/src/testsda -l gtsda
#ÆäËü¿â
CXXFLAGS += -L/workplace/mywork/svn/GTIP-E_studio/src/testsda/lib -lpthread  -lsda -lsgutils2 -lmedia_api -lgtlog

CXXFLAGS += $(INCLUDES) $(LIBS)
OBJDIR = $(TOP)/OUT
SRCS = $(wildcard $(TOP)/src/*.cpp)
dir=$(notdir $(SRCS))
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(dir))
all: mediaserver



#$@
mediaserver: $(OBJS)
	$(CXX) -o mediaserver $^ $(CXXFLAGS) 
	cp mediaserver /mnt/yk

$(OBJDIR)/%.o:%.cpp
	$(CXX) -c -o $@ $<  $(CXXFLAGS)
	
	
	
	
	
	
	
	
	
	
	
	
	

live555top = /workplace/mywork/test/live-arm


USAGE_ENVIRONMENT_DIR = $(live555top)/UsageEnvironment
USAGE_ENVIRONMENT_LIB = $(USAGE_ENVIRONMENT_DIR)/libUsageEnvironment.a
BASIC_USAGE_ENVIRONMENT_DIR = $(live555top)/BasicUsageEnvironment
BASIC_USAGE_ENVIRONMENT_LIB = $(BASIC_USAGE_ENVIRONMENT_DIR)/libBasicUsageEnvironment.a
LIVEMEDIA_DIR = $(live555top)/liveMedia
LIVEMEDIA_LIB = $(LIVEMEDIA_DIR)/libliveMedia.a
GROUPSOCK_DIR = $(live555top)/groupsock
GROUPSOCK_LIB = $(GROUPSOCK_DIR)/libgroupsock.a
LOCAL_LIBS =	$(LIVEMEDIA_LIB) $(GROUPSOCK_LIB) \
		$(BASIC_USAGE_ENVIRONMENT_LIB) $(USAGE_ENVIRONMENT_LIB)
LIBS =			$(LOCAL_LIBS) $(LIBS_FOR_CONSOLE_APPLICATION)

live555MediaServer$(EXE):	$(MEDIA_SERVER_OBJS) $(LOCAL_LIBS)
	$(LINK)$@ $(CONSOLE_LINK_OPTS) $(MEDIA_SERVER_OBJS) $(LIBS)
	
		
print:
	echo $(SRCS)
	echo $(OBJS)
	echo $(OBJDIR)/%.o
	echo ""
	
.PHONY: clean	
clean:
	rm $(OBJS) 
	rm mediaserver