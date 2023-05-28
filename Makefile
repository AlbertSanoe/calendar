TOPDIR=$(PWD)
BINDIR=$(TOPDIR)/bin
OBJDIR=$(TOPDIR)/obj
SRCDIR=$(TOPDIR)/src

ALL_OBJFILES=$(wildcard $(OBJDIR)/*.o)
TEST_OBJFILES=$(filter $(OBJDIR)/test@%.o,$(ALL_OBJFILES))

TEST_EXECUTABLE=test@main
EXECUTABLE=main

HAS_EXECUTABLES=$(wildcard $(BINDIR)/*)
HAS_EXEUTABLE=$(filter-out $(BINDIR)/test@%,$(HAS_EXECUTABLES))
HAS_TEST_EXECUTABLE=$(filter $(BINDIR)/test@%,$(HAS_EXECUTABLES))

MAKE_TEST_OPTION =trial

PRINT_DIR=--no-print-directory

MODE =DEBUG
SILENT_OPTION=-s
#MODE=RELEASE
# DEBUG/ RELEASE

.PHONY: all run run_test build build_test 
.PHONY: clean clean_test clean_exe clean_testexe clean_obj clean_testobj
.PHONY: pathinfo

all:
ifeq ($(MODE),RELEASE)
	$(eval slient=$(SILENT_OPTION))
else ifeq ($(MODE),DEBUG)
	$(eval slient=)
else
	$(error Bad MODE: assign it DEBUG/ RELEASE)
endif
ifneq ($(HAS_EXEUTABLE),)
	@$(MAKE) run $(slient)
else ifneq ($(HAS_TEST_EXECUTABLE),)
	@$(MAKE) run_test $(slient)
else
	@$(MAKE) run $(slient)
endif

run: $(BINDIR)/$(EXECUTABLE)
	@$(BINDIR)/$(EXECUTABLE)

run_test: $(BINDIR)/$(TEST_EXECUTABLE)
	@$(BINDIR)/$(TEST_EXECUTABLE)

$(BINDIR)/$(EXECUTABLE):
	@echo Compiling to executable..
ifeq ($(MODE),RELEASE)
	@cd $(SRCDIR) && $(MAKE) $(SILENT_OPTION) $(PRINT_DIR)
else ifeq ($(MODE),DEBUG)
	@cd $(SRCDIR) && $(MAKE) 
else
	$(error Bad MODE: assign it DEBUG/ RELEASE)
endif
	@echo Compiling is done..

$(BINDIR)/$(TEST_EXECUTABLE):
	@echo Compiling to test executable..
ifeq ($(MODE),RELEASE)
	@cd $(SRCDIR) && $(MAKE) $(SILENT_OPTION) $(MAKE_TEST_OPTION) $(PRINT_DIR)
else ifeq ($(MODE),DEBUG)
	@cd $(SRCDIR) && $(MAKE) $(MAKE_TEST_OPTION) 
else
	$(error Bad MODE: assign it DEBUG/ RELEASE)
endif
	@echo Compiling is done..

build:
	@rm -rf $(HAS_EXEUTABLE) || exit 1
	@echo Compiling to executable..
ifeq ($(MODE),RELEASE)
	@cd $(SRCDIR) && $(MAKE) $(SILENT_OPTION) $(PRINT_DIR)
else ifeq ($(MODE),DEBUG)
	@cd $(SRCDIR) && $(MAKE) 
else
	$(error Bad MODE: assign it DEBUG/ RELEASE)
endif
	@echo Compiling is done..

build_test:
	@rm -rf $(HAS_TEST_EXECUTABLE) || exit 1
	@echo Compiling to test executable..
ifeq ($(MODE),RELEASE)
	@cd $(SRCDIR) && $(MAKE) $(SILENT_OPTION) $(MAKE_TEST_OPTION) $(PRINT_DIR)
else ifeq ($(MODE),DEBUG)
	@cd $(SRCDIR) && $(MAKE) $(MAKE_TEST_OPTION) 
else
	$(error Bad MODE: assign it DEBUG/ RELEASE)
endif
	@echo Compiling is done..

clean: 
	@rm -rf $(HAS_EXECUTABLES) || exit 1
	@rm -rf $(ALL_OBJFILES) || exit 1
	@echo Executable files and object files are removed.

clean_test:
	@rm -rf $(HAS_TEST_EXECUTABLE) || exit 1
	@rm -rf $(TEST_OBJFILES) || exit 1
	@echo Test files are removed.

clean_exe:
	@rm -rf $(HAS_EXECUTABLES) || exit 1
	@echo Executable files are removed.

clean_testexe:
	@rm -rf $(HAS_TEST_EXECUTABLE) || exit 1
	@echo Test executable files are removed.

clean_obj:
	@rm -rf $(ALL_OBJFILES) || exit 1
	@echo Object files are removed.

clean_testobj:
	@rm -rf $(TEST_OBJFILES) || exit 1
	@echo Test object files are removed. 

pathinfo:
	@echo Top Directory: 	$(TOPDIR)
	@echo Binary Directory: $(BINDIR)
	@echo Object Directory:	$(OBJDIR)
	@echo Source Directory: $(SRCDIR)

export MODE
export TOPDIR BINDIR OBJDIR SRCDIR
export EXECUTABLE TEST_EXECUTABLE