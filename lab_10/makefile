.PHONY : run clean

SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out

CC := gcc
ASM := nasm
CFLAGS := -std=gnu11 -O0 -w -I$(INC_DIR) -masm=intel

SRCS := $(wildcard $(SRC_DIR)/*.c)
INCS := $(filter-out $(INC_DIR)/main.h, $(SRCS:$(SRC_DIR)/%.c=$(INC_DIR)/%.h))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

EXEC := main.exe

$(EXEC) : CFLAGS += -m80387
$(EXEC) : $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

${OUT_DIR}/%.o : ${SRC_DIR}/%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	@./$<

clean:
	@$(RM) $(EXEC) ${OUT_DIR}/*
	@rm -rf $(OUT_DIR)
