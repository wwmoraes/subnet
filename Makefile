CXXFLAGS ?= -std=c++17 -Wall -Wextra -Og -g -pedantic
BIN := subnet
ARGS := 10.1.0.1/24 10.0.0.1/16
SOURCE_FILES := $(wildcard *.cc)
OBJECT_FILES := $(patsubst %.cc,%.o,$(SOURCE_FILES))
PROFILE_DIR := $(BIN).profile

COLOR := $(shell tput setaf 6)
RESET := $(shell tput sgr0)

.DEFAULT_GOAL := subnet

.SUFFIXES:
	MAKEFLAGS += -rRf

.PHONY: all
all: clean $(BIN)

.PHONY: clean
clean:
	$(info cleaning objects and binary...)
	@$(RM) $(BIN) $(OBJECT_FILES)

$(BIN): $(OBJECT_FILES)
	$(info compiling $(COLOR)$@$(RESET)...)
	@$(CXX) -o $@ $^ $(CXXFLAGS)

main.o: main.cc
	$(info compiling $(COLOR)$@$(RESET)...)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

%.o: %.cc %.hh
	$(info compiling $(COLOR)$@$(RESET)...)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

run: $(BIN)
	@exec ./$(BIN) $(ARGS)

valgrind: $(BIN)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(BIN) $(ARGS)


.PHONY: profile-clean
profile-clean: ht-clean massif-clean

.PHONY: ht
ht: ht-build ht-view

.PHONY: ht-build
ht-build: $(BIN)
	@mkdir -p $(PROFILE_DIR)
	@heaptrack ./$(BIN) $(ARGS)
	@mv -t $(PROFILE_DIR) heaptrack.$(BIN).*.gz

.PHONY: ht-view
ht-view:
	@heaptrack --analyze $(shell ls -t $(PROFILE_DIR)/heaptrack.$(BIN).*.gz | head -n1)

.PHONY: ht-compare
ht-compare:
	@heaptrack --analyze -d $(shell ls -t $(PROFILE_DIR)/heaptrack.$(BIN).*.gz | head -n2)

.PHONY: ht-clean
ht-clean:
	-@rm -f $(PROFILE_DIR)/heaptrack.$(BIN).*.gz

.PHONY: massif
massif: massif-build massif-view

.PHONY: massif-build
massif-build: $(BIN)
	@mkdir -p $(PROFILE_DIR)
	@valgrind --tool=massif ./$(BIN) $(ARGS)
	@mv -f massif.out.* $(PROFILE_DIR)

.PHONY: massif-view
massif-view:
	@massif-visualizer $(shell ls -t $(PROFILE_DIR)/massif.out.* | head -n1)

.PHONY: massif-clean
massif-clean:
	-@rm -f $(PROFILE_DIR)/massif.out*
