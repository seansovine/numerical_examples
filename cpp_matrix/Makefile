# Build and run the program.

filename=matrix

all:
	@echo "Building..."
	g++ -Wall $(filename).cpp -o build/$(filename)

runner:
	@./build/$(filename)

run_only: runner

break:
	@echo "\n------\n"

.PHONY: runner
run: all break runner
