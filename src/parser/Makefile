LOCAL_FLAG=parser$(DELIMITER)
LOCAL_FILES =$(wildcard *.cpp)
LOCAL_PREFIX=$(OBJDIR)/$(LOCAL_FLAG)
LOCAL_OBJFILES =$(LOCAL_FILES:%.cpp=$(LOCAL_PREFIX)%.o)

.PHONY: all local

all: local

local: $(LOCAL_OBJFILES)

$(LOCAL_PREFIX)%.o:%.cpp

	$(ECHO)$(CXX) $(CXXFLAGS) $< -o $@