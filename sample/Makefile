SRCS := client.c echo.c keycontrol.c pidcontrol.c
PROGS := $(SRCS:.c=)

CC := gcc
CFLAGS := -Wall

.PHONY: all
all: $(PROGS)

$(PROGS): private.h ../bcontroller.c

.PHONY: clean
clean:
	$(RM) $(PROGS)
