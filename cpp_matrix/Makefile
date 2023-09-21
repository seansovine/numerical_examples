# Build and run the program.
#  For use by the bld shell script.

# Set by bld:
# main_filename=markov_iteration
# main_filename=matrix_test

flags=-Wall #-std=c++11 -- Uncomment for testing.

all:
	@echo "Building..."
	g++ $(flags) $(main_filename).cpp -o build/$(main_filename)

runner:
	@./build/$(main_filename)

run_only: runner

break:
	@echo "\n------\n"

.PHONY: runner
run: all break runner
