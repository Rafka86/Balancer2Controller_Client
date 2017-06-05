SRCS := client.c echo.c keycontrol.c pidcontrol.c
PROGS := $(SRCS:.c=)

CC := gcc
CFLAGS := -Wall

.PHONY: all
all: $(PROGS)

$(PROGS): ../bcontroller.c

rlcontrol2: ../bcontroller.c mt19937ar-cok.c

.PHONY: clean
clean:
	$(RM) $(PROGS)
