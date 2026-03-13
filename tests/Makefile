CXX := g++
CXXFLAGS := -I.. -Wall -Wextra -std=c++20 
LDLIBS := -lgtest -lgtest_main -lpthread

# LDLIBS += -fsanitize=address,undefined
# CXXFLAGS += -fsanitize=address,undefined


OBJ_DIR := build

TEST_SRCS := $(wildcard *.cc)
TEST_OBJS := $(patsubst %.cc,$(OBJ_DIR)/test_%.o,$(TEST_SRCS))

GRAPH_SRCS := $(wildcard ../graph_lib/*.cc)
ALGOS_SRCS := $(wildcard ../algos_lib/*.cc)
CONTAINERS_SRCS := $(wildcard ../containers/*.cc)


GRAPH_OBJS := $(patsubst ../%.cc,$(OBJ_DIR)/%.o,$(GRAPH_SRCS))
ALGOS_OBJS := $(patsubst ../%.cc,$(OBJ_DIR)/%.o,$(ALGOS_SRCS))
CONTAINERS_OBJS := $(patsubst ../%.cc,$(OBJ_DIR)/%.o,$(CONTAINERS_SRCS))


MODEL_OBJS := $(GRAPH_OBJS) $(ALGOS_OBJS) $(CONTAINERS_OBJS)


TARGET := test_exec

$(TARGET): $(MODEL_OBJS) $(TEST_OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: ../%.cc | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test_%.o: %.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


.PHONY: all test coverage clean clean-coverage valgrind-run

all: clean $(TARGET)

test: clean $(TARGET)
	./$(TARGET)


COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage
COVERAGE_INFO := coverage.info
COVERAGE_REPORT_DIR := ../report


coverage: CXXFLAGS += $(COVERAGE_FLAGS)
coverage: LDLIBS += -lgcov
coverage: clean test
	mkdir -p $(COVERAGE_REPORT_DIR)
	gcovr --root .. \
		--filter ../graph_lib/ \
		--filter ../algos_lib/ \
		--html-details $(COVERAGE_REPORT_DIR)/report.html \
		--exclude-branches-by-pattern '.*'



clean: clean-coverage
	rm -rf $(OBJ_DIR) $(TARGET)

clean-coverage:
	rm -rf $(COVERAGE_REPORT_DIR) *.gcov *gcno *gcda


leaks: all
	valgrind \
		--leak-check=full \
		--track-origins=yes \
		--show-leak-kinds=all \
		--trace-children=yes \
		-s \
		./$(TARGET)

profile: all
	valgrind --tool=callgrind \
		--dump-instr=yes \
		--simulate-cache=yes \
		--collect-jumps=yes \
		./$(TARGET)


cachegrind:
	valgrind --tool=cachegrind ./$(TARGET)