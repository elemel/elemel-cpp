TEST_SRCS := $(notdir $(wildcard *_test.cpp))
TEST_DEPS := $(TEST_SRCS:.cpp=.d)
TEST_PROGS := $(TEST_SRCS:.cpp=)
PASSED_FILES := $(TEST_SRCS:.cpp=.passed)

CPPFLAGS := -I../include -MMD

all: $(PASSED_FILES)

$(TEST_PROGS):

%.passed: %
	./$<
	echo passed > $@

%: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f *_test *.passed *.d

.PHONY: all clean

-include $(TEST_DEPS)
