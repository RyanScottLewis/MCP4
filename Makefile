# == Constants =========================================================================================================

PROJECT = tdled
SOURCE  = src
TESTS   = test

TARGET = $(shell gcc -dumpmachine)
BUILD  = build/$(TARGET)

TESTS_BUILD    = $(BUILD)/test
TESTS_SOURCES  = $(wildcard $(TESTS)/*.cpp)
TESTS_BINARIES = $(patsubst $(TESTS)/%.cpp, $(TESTS_BUILD)/%, $(TESTS_SOURCES))
TESTS_INCLUDES = $(SOURCE) lib

# == Compiler Flags ====================================================================================================

# =- Common -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CFLAGS_COMMON  = $(CFLAGS)

# -- Warnings ----------------------------------------------------------------------------------------------------------

# This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid.
CFLAGS_COMMON += -Wall

# Warn if a function is declared or defined without specifying the argument types.
CFLAGS_COMMON += -Wstrict-prototypes

# Warn if a function that is declared as inline cannot be inlined.
CFLAGS_COMMON += -Winline

# -- Optimizations -----------------------------------------------------------------------------------------------------

# # Standard
CFLAGS_COMMON += -std=c++11
# CFLAGS_COMMON += -std=gnu++11

# =- Tests -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

TESTS_CFLAGS  = $(CFLAGS_COMMON)
TESTS_CFLAGS += $(foreach p, $(TESTS_INCLUDES), -I $p)

# Don't optimize really like at all, man.
TESTS_CFLAGS += -O0

# == Targets ===========================================================================================================

$(TESTS_BUILD):
	@echo DIR $@
	@mkdir -p $@

$(TESTS_BUILD)/%: $(TESTS)/%.cpp $(TESTS_BUILD)
	@echo CC+LD $@
	@g++ $(TESTS_CFLAGS) -o $@ $<

# == Tasks =============================================================================================================

.PHONY: clean
clean:
	@rm -rf build

.PHONY: format
format:
	@echo FMT
	@clang-format -i src/*
	@clang-format -i test/*

.PHONY: list
list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$' | cut -d ":" -f 1

# Serial tests - ~67s total
.PHONY: tests
tests: $(TESTS_BINARIES)

# Parallel tests - 10 test files (when benchmarked) - 4 jobs = ~29s total - 10 jobs = ~23s total
.PHONY: test
test:
	echo $(TESTS_BINARIES) | tr " " "\n" | parallel -u -j 12 "make {}"
	echo $(TESTS_BINARIES) | tr " " "\n" | parallel -u -j 12 "{}"
	# ./$@
