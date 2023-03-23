
C_FILES := $(wildcard *.c)
O_FILES := $(patsubst %.c, %.o, $(C_FILES))
O_FILES := $(addprefix build/, $(O_FILES))
H_FILES := testBoards.h minimax.h
OUTPUT_FILE := minmax
CC := gcc

all: $(OUTPUT_FILE)




build/%.o: %.c $(H_FILES)
	$(CC) -c $< -o $@

$(OUTPUT_FILE): $(O_FILES) $(H_FILES)
	$(CC) $(O_FILES) -g -o $@ 
