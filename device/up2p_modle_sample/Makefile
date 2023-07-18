include ./config.mk

INC_DIR := demo common protocol
INC := $(patsubst %,-I%/include,$(INC_DIR))
INC += -I./sdk/$(PLATFORM)/include
LIB := $(patsubst %,-L%/$(PLATFORM)/lib,$(INC_DIR))
LIB += -L./sdk/$(PLATFORM)/lib

SRC := $(wildcard *.cpp *.c $(patsubst %,%/src/*.cpp,$(INC_DIR)) $(patsubst %,%/src/*.c,$(INC_DIR)))
OBJ := $(patsubst %.cpp,%.obj,$(patsubst %.c,%.o,$(SRC)))
DEP := $(patsubst %.obj,%.dep,$(patsubst %.o,%.d,$(OBJ)))

CC := $(COMPILE_PREFIX)gcc
CFLAGS = $(INC) -g -O0 -Wall -DBSD=1 -fPIC $(CFLAGS_FLAGS)
CXX := $(COMPILE_PREFIX)g++
CXXFLAGS := $(CFLAGS)
LINK := $(COMPILE_PREFIX)g++ -o 
LIBRARY_LINK := $(COMPILE_PREFIX)g++ -shared -o
LIBRARY_LINK_STATIC := $(COMPILE_PREFIX)ar cr
LIBRARY_LINK_OPTS =	$(LDFLAGS_FLAGS) -Wl,--start-group -lup2p_sdk -lp2p_core -lpthread -lm -ldl -lrt -Wl,--end-group -Wl,--gc-sections
ifeq ($(PLATFORM), linux)
LIBRARY_LINK_OPTS += -liconv -luuid 
endif
STRIP := $(COMPILE_PREFIX)strip

TARGET := sample

.PHONY : all clean

all : $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c $< -o $@

%.obj : %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -MF"$(@:%.obj=%.dep)" -MT"$(@:%.obj=%.dep)" -c $< -o $@

$(TARGET) : $(OBJ)
	$(LINK) $@ $^  $(LIB) $(LIBRARY_LINK_OPTS)
	
clean:
	@rm -rf $(OBJ) $(DEP) $(TARGET)
	
sinclude $(DEP)


