# Day09：管道、FIFO、select 与信号

## 学习主题与知识点

使用匿名管道在父子进程间通信，用两个命名管道连接独立进程；使用 `select` 同时等待标准输入和管道，并体验 SIGINT、SIGTSTP 的处理。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `pipetwo.c` | 创建两个匿名管道，父进程发送消息，子进程回复 done!；关闭各自不用的端点。 |
| `FIFO.c` | 打开 pipe1 写端、pipe2 读端，发送终端输入并读取回复。 |
| `FIFO1.c` | 打开 pipe1 读端、pipe2 写端，与 FIFO 配对通信。 |
| `select.c` | 父进程监听标准输入和管道，子进程约 3 秒后发送消息；处理 EINTR 和 EOF 并回收子进程。 |
| `sign.c` | 注册 SIGINT、SIGTSTP 处理函数后持续循环。 |
| `Makefile` | 每个 C 文件独立生成同名程序；`run` 构建并运行 select。 |
| 无扩展名程序 | 仓库已有编译产物。 |

## 编译与运行

使用 Linux、GCC、GNU Make。源码依赖未随仓库提供的自定义 `<func.h>`。先准备原学习环境的头文件及依赖；`sign.c` 使用 GNU 类型 `sighandler_t`，编译时启用 `_GNU_SOURCE`。

从本目录编译到临时目录，避免复用已有二进制：

```bash
export FUNC_INCLUDE=/absolute/path/to/headers
build=$(mktemp -d)
for src in *.c; do
    gcc -D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g \
        -I"$FUNC_INCLUDE" "$src" -o "$build/${src%.c}" || break
done
"$build/pipetwo"
"$build/select"
```

`select` 可输入一行文字，也可等待子进程消息；管道到达 EOF 后退出。若希望使用原 Makefile，可执行下面命令；`-B` 强制重新构建已有目标，它会覆盖本目录同名编译产物：

```bash
make -B CFLAGS="-D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g -I$FUNC_INCLUDE"
make run
```

FIFO 示例先在一个新的临时目录创建管道，再用两个终端进入该目录。下面的 `$build` 指上面编译输出的绝对路径；第二个终端需设置成相同值：

```bash
# 终端 1
cd "$build"
mkfifo pipe1 pipe2
./FIFO

# 终端 2（进入同一个 build 目录）
cd "$build"
./FIFO1
```

两个程序都先从各自终端读取一行再等待对端，所以需在两个终端都输入内容才能完成一轮。打开 FIFO 时等待对端是正常的阻塞行为。现有接收代码没有按 read 的返回值补字符串结束符，显示结果可能包含多余内容，不能将其当作完整可靠的聊天实现。

单独运行 `"$build/sign"` 后按 Ctrl+C、Ctrl+Z 可观察捕获结果；它们已被处理，不会按默认方式终止或暂停。可从另一个终端通过 `kill -TERM <该进程PID>` 结束程序。

## 练习目标

- 能画出两条管道的读写方向，解释为何要关闭不用的端点。
- 能说明 FIFO 的打开阻塞、收发顺序和 EOF 条件。
- 能在每次 select 前重建集合，并根据就绪集合区分输入来源。
- 理解本目录信号示例的局限：空循环消耗 CPU，处理函数中的 printf 不是异步信号安全函数。
