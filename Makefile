CC = gcc
CFLAGS = -Wall -O0 -g
MYSQL_FLAGS = $(shell mysql_config --cflags --libs)

SRC = supervisor_v3.c \
      mysql_utils/mysql_utils_v2.c \
      dasgip_utils/dasgip_utils_v2.c

TARGET = main

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(MYSQL_FLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
