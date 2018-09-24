CC := gcc
CFLAGS := `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_net -Wall
# -ggdb3 -O0 --std=c99 -lm

HDRS := cJSON.h error.h networking.h payloads.h

SRCS := main.c cJSON.c error.c networking.c payloads.c
OBJS := $(SRCS:.c=.o)
EXEC := main.build

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(OBJS)
	# rm -f $(EXEC) $(OBJS)

.PHONY: all clean