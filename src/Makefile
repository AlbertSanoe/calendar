CXX =g++
CXXFLAGS =-c
CPPFLAGS = 
LDFLAGS=-lm
WFLAGS =-Wall

LOCAL_PATH=$(SRCDIR)
DATATYPE_PATH=$(LOCAL_PATH)/datatype
IO_PATH=$(LOCAL_PATH)/io
MACRO_PATH=$(LOCAL_PATH)/macro
PARSER_PATH=$(LOCAL_PATH)/parser
TABLE_PATH=$(LOCAL_PATH)/table
TEST_PATH=$(LOCAL_PATH)/test

LOCAL_FLAG=
DELIMITER=@
LOCAL_PREFIX=$(OBJDIR)/$(LOCAL_FLAG)

LOCAL_FILES =$(wildcard *.cpp)
LOCAL_OBJFILES =$(LOCAL_FILES:%.cpp=$(LOCAL_PREFIX)%.o)

ALL_OBJFILES=$(wildcard $(OBJDIR)/*.o)
FOR_EXECUTED_OBJFILES=$(filter-out $(OBJDIR)/test@%.o,$(ALL_OBJFILES))
FOR_TEST_OBJFILES=$(filter-out $(OBJDIR)/main%.o,$(ALL_OBJFILES))

ifeq ($(MODE),DEBUG)
ECHO=
else
ECHO=@
endif

.PHONY: all app local macro parser io table test trial

$(LOCAL_PREFIX)%.o:%.cpp
	$(ECHO)$(CXX) $(CXXFLAGS) $< -o $@

all:local app io macro parser table $(BINDIR)/$(EXECUTABLE)

trial:app io macro parser table test $(BINDIR)/$(TEST_EXECUTABLE)  

$(BINDIR)/$(EXECUTABLE):
	$(ECHO)$(CXX) $(LDFLAGS) $(FOR_EXECUTED_OBJFILES) -o $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(TEST_EXECUTABLE):
	$(ECHO)$(CXX) $(LDFLAGS) $(FOR_TEST_OBJFILES) -o $(BINDIR)/$(TEST_EXECUTABLE)


local: $(LOCAL_OBJFILES)

app:
	$(ECHO)cd $(DATATYPE_PATH) && $(MAKE) $(PRINT_DIR)

io:
	$(ECHO)cd $(IO_PATH) && $(MAKE) $(PRINT_DIR)

macro:
	$(ECHO)cd $(MACRO_PATH) && $(MAKE) $(PRINT_DIR)

parser:
	$(ECHO)cd $(PARSER_PATH) && $(MAKE) $(PRINT_DIR)

table:
	$(ECHO)cd $(TABLE_PATH)  && $(MAKE) $(PRINT_DIR)

test:
	$(ECHO)cd $(TEST_PATH) && $(MAKE) $(PRINT_DIR)

info:
	@echo "CXX" = $(CXX) 
	@echo "CC" = $(CC)
	@echo "RM" = $(RM)
	@echo "CXXFLAGS" = $(CXXFLAGS) 
	@echo "CPPFLAGS" = $(CPPFLAGS)

export TOPDIR BINDIR OBJDIR SRCDIR
export CXX CXXFLAGS CPPFLAGS WFLAGS
export PRINT_DIR ECHO
export DELIMITER