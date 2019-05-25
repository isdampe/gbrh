CXX = gcc
src = $(wildcard src/*.c)
obj = $(src:.c=.o)

LDFLAGS = -Wall -Wextra -std=c14 -O3

gbrh: $(obj)
	@mkdir -p bin
	$(CXX) -g -o bin/$@ $^ $(LDFLAGS) $(OSFLAGS)

clean:
	rm $(obj)

install:
	@cp bin/gbrh /usr/local/bin/gbrh

uninstall:
	@rm /usr/local/bin/gbrh
