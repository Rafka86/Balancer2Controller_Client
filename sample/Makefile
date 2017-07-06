SRCS := client.c echo.c keycontrol.c pidcontrol.c
PROGS := $(SRCS:.c=)

CC := gcc
CFLAGS := -Wall
LDLIBS := -lbb2d

.PHONY: all
all: $(PROGS)

$(PROGS): ../bb2c4rl.c

rlcontrol2: ../bb2c4rl.c mt19937ar-cok.c

.PHONY: clean
clean:
	$(RM) $(PROGS)
