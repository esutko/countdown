src = $(wildcard src/*.cc)
objects = $(src:src/%.cc=out/%.o)
dependencies = $(obj:.o=.d)

tests = $(wildcard test/*.cc)
tests_objs = $(tests:test/%.cc=out/tests/%.o)
tests_deps = $(tests_objs:.o=.d)

test_lib = $(wildcard test/lib/*.cc)
test_lib_objs = $(test_lib:test/lib/%.cc=out/test_lib/%.o)
test_lib_deps = $(test_lib_objs:.o=.d)

CXX = g++
CXXFLAGS = -std=c++17 -MMD -Wall -Wextra -Wpedantic -Werror -Wfatal-errors \
		   -fprofile-arcs -ftest-coverage

# countdown

countdown: $(objects)
	$(CXX) $(CXXFLAGS) $^ -o $@

-include $(dependencies)

out/%.o: src/%.cc | out
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# testing

-include $(tests_deps)
-include $(test_lib_deps)

run_tests: $(filter-out out/main.o, $(objects)) $(tests_objs) $(test_lib_objs)
	$(CXX) $(CXXFLAGS) $^ -o $@

out/tests/%.o: test/%.cc | out/tests
	$(CXX) $(CXXFLAGS) -o $@ -c $<

out/test_lib/%.o: test/lib/%.cc | out/test_lib
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# directories

out:
	mkdir $@

out/tests: | out
	mkdir $@

out/test_lib: | out
	mkdir $@

# misc targets

.Phony : test clean install count

test: run_tests
	./run_tests

clean:
	rm -rf countdown run_tests *.gcov out

install: countdown
	cp countdown run_tests ~/.local/bin

count:
	wc -l src/*
