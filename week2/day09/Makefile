
# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Wextra -g

# 自动查找当前目录中的所有 .c 文件
SRCS = $(wildcard *.c)

# 将 select.c 转换为 select
# 将 pipetwo.c 转换为 pipetwo
TARGETS = $(SRCS:.c=)

# 默认编译全部程序
all: $(TARGETS)

# 通用编译规则
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# 编译并运行 select
run: select
	./select

# 清理生成的可执行文件
clean:
	rm -f $(TARGETS)

.PHONY: all run clean

