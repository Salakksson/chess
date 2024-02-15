CC         	= gcc
CFLAGS		= -Wall -I/usr/include -O3 -g
LDFLAGS		= -lraylib -lm

DIR_SRC     = ./src
DIR_BUILD   = ./bin

PLATFORM 	= linux

TARGET      = chess

CC         	= clang
# PLATFORM 	= macos

SRCS        = $(wildcard $(DIR_SRC)/*.c)
OBJS        = $(filter-out $(DIR_BUILD)/main.o, $(patsubst $(DIR_SRC)/%.c, $(DIR_BUILD)/%.o, $(SRCS)))

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS) $(DIR_BUILD)/main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	# @cp ./$(TARGET) release/$(PLATFORM)/
	# cp -r ./assets release/$(PLATFORM)/

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
.PHONY: clean

clean:
	rm -rf $(DIR_BUILD)/*.o

.PHONY: init

init:
	mkdir 	DIR_BUILD