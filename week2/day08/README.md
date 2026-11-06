# Day08：进程创建、资源继承与回收

## 学习主题与知识点

学习 `fork` 的父子分支、进程标识、内存副本、继承文件描述符，以及 `waitpid` 回收子进程和解析退出状态。比较“独立的变量值”和“共享的打开文件偏移量”。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `fork.c` | 打印父子进程 PID/PPID，观察 `fork` 返回值和输出顺序。 |
| `forkdata.c` | 子进程修改全局、栈和堆变量，父进程稍后打印自己的变量值。 |
| `forkfile.c` | 在 fork 前打开 `shared.txt`；子进程写 HELLO，父进程等待后查看偏移并写 WORLD。 |
| `waitpid.c` | 子进程休眠后以 42 退出，父进程等待并解析退出码。 |
| `shared.txt` | 文件偏移共享示例的数据文件；运行 `forkfile` 会清空并重写。 |
| 无扩展名程序 | 已有编译产物。 |

## 编译与运行

使用 Linux、GCC；本目录没有 Makefile。源码依赖自定义 `<func.h>`，仓库未附带它。先准备原学习环境的头文件及依赖（包括进程、文件 I/O 和 wait 系列声明），再从本目录执行：

```bash
export FUNC_INCLUDE=/absolute/path/to/headers
build=$(mktemp -d)
for src in *.c; do
    gcc -D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g \
        -I"$FUNC_INCLUDE" "$src" -o "$build/${src%.c}" || break
done
cd "$build"
./fork
./forkdata
./forkfile
cat shared.txt
./waitpid
```

在临时目录运行可避免改写仓库的 `shared.txt`。正常情况下，`forkdata` 的子进程打印 1100、1200、1300，父进程仍为 100、200、300；`forkfile` 打印偏移量 5，最终文件为 `HELLOWORLD`；`waitpid` 打印退出码 42。

## 练习目标

- 能根据 `fork` 的返回值辨认当前执行分支，并解释父子输出顺序为何可能变化。
- 能说明普通全局、栈和堆变量在 fork 后不是可直接互相修改的共享内存。
- 能解释继承描述符为何共享偏移量，以及等待子进程如何保证本例写入顺序。
- 理解标准输出缓冲也会被复制：fork 前没有换行的 `begin:` 可能出现重复输出。
- 阅读现有错误分支：部分 switch 的 `case -1` 缺少跳出，不能把 fork 失败后的输出当作成功创建子进程。
