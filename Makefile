CXX = g++

BUILD_DIR := build

CXXFLAGS := -std=c++20 -Wall -Wextra -Werror
CXXFLAGS += -O2 -DNDEBUG

# LDLIBS += -fsanitize=address,undefined
# CXXFLAGS += -fsanitize=address,undefined

GRAPH_SRC := $(wildcard graph_lib/*.cc)
ALGOS_SRC := $(wildcard algos_lib/*.cc)
CONTAINERS_SRC := $(wildcard containers/*.cc)
CONTROLLER_SRC := $(wildcard controller/*.cc)
UI_SRC := $(wildcard ui/*.cc)

GRAPH_OBJ := $(addprefix $(BUILD_DIR)/,$(GRAPH_SRC:.cc=.o))
ALGOS_OBJ := $(addprefix $(BUILD_DIR)/,$(ALGOS_SRC:.cc=.o))
CONTAINERS_OBJ := $(addprefix $(BUILD_DIR)/,$(CONTAINERS_SRC:.cc=.o))
CONTROLLER_OBJ := $(addprefix $(BUILD_DIR)/,$(CONTROLLER_SRC:.cc=.o))
UI_OBJ := $(addprefix $(BUILD_DIR)/,$(UI_SRC:.cc=.o))

MAIN_SRC := main.cc
MAIN_OBJ := $(BUILD_DIR)/main.o

EXECUTABLE := graph

.PHONY: all clean test cl cppcheck_cpp gcov_report valgrind

all: s21_graph.a s21_graph_algorithms.a containers.a graph

$(EXECUTABLE): $(MAIN_OBJ) $(CONTROLLER_OBJ) $(UI_OBJ) s21_graph.a s21_graph_algorithms.a containers.a
	$(CXX) $(CXXFLAGS) $(MAIN_OBJ) $(CONTROLLER_OBJ) $(UI_OBJ) -L. -l:s21_graph.a -l:s21_graph_algorithms.a -l:containers.a -o $@

$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

s21_graph.a: $(GRAPH_OBJ)
	ar rcs $@ $^

s21_graph_algorithms.a: $(ALGOS_OBJ)
	ar rcs $@ $^

containers.a: $(CONTAINERS_OBJ)
	ar rcs $@ $^


.PHONY: all clean test cl cppcheck_cpp gcov_report valgrind


clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE) *.a
	$(MAKE) -C tests/ clean

cl:
	cp ../materials/linters/.clang-format .clang-format
	find . -type f -name "*.cc" -o -name "*.h" | xargs clang-format -i
	rm -f .clang-format

cppcheck_cpp:
	cppcheck --enable=all --force --error-exitcode=1 --suppress=unusedFunction --std=c++20 --suppress=missingIncludeSystem --inconclusive --language=c++ \
	--check-level=exhaustive --verbose ../src

test:
	$(MAKE) -C tests/ test

gcov_report:
	$(MAKE) -C tests/ coverage

valgrind:
	$(MAKE) -C tests/ leaks





