SRCS := client.c echo.c keycontrol.c
PROGS := $(SRCS:.c=)

CC := gcc
CFLAGS := -Wall

.PHONY: all
all: $(PROGS)

$(PROGS): ../bcontroller.c

.PHONY: clean
clean:
	$(RM) $(PROGS)
