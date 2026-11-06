# Day10：POSIX 线程的创建、传参、回收与取消

## 学习主题与知识点

学习 `pthread_create`、线程标识、参数生命周期、`pthread_join`、线程返回值、取消请求和清理处理函数。通过两个线程分别求和体验任务拆分。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `thread-create.c` | 创建工作线程，打印线程 ID 和共同的进程 ID。 |
| `threadexit.c` | 当前内容与 thread-create.c 相同，工作线程 return NULL；没有单独调用 pthread_exit。 |
| `threadval.c` | 将主线程栈上的结构体地址传给工作线程，打印 1、2、4。 |
| `t_join.c` | 尝试等待线程并接收 1234，但当前返回值接收方式存在类型和大小问题。 |
| `addtwonum.c` | 输入 n，两个线程分别计算 1 到 n/2、n/2+1 到 n 的和，再合并。 |
| `t_cancel.c` | 注册清理处理函数，约 2 秒后请求取消工作线程，join 后检查 PTHREAD_CANCELED。 |
| `Makefile` | 每个 C 文件独立编译；默认选项未指定 -pthread，run 仍指向不存在的 select。 |
| 无扩展名程序 | 已有编译产物。 |

## 编译与运行

使用 Linux、GCC 和 POSIX 线程库。全部源码依赖自定义 `<func.h>`，仓库未提供；先准备原学习环境的头文件及依赖（包含 pthread 等声明）。

从本目录将程序编译到临时目录：

```bash
export FUNC_INCLUDE=/absolute/path/to/headers
build=$(mktemp -d)
for src in *.c; do
    gcc -D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g -pthread \
        -I"$FUNC_INCLUDE" "$src" -o "$build/${src%.c}" || break
done
"$build/thread-create"
"$build/threadexit"
"$build/threadval"
printf '10\n' | "$build/addtwonum"
"$build/t_cancel"
```

求和示例在相应平台上预期打印 55；取消示例预期执行清理函数并报告线程被取消。也可覆盖原 Makefile 的选项并强制重编译，但会覆盖本目录同名编译产物：

```bash
make -B CFLAGS="-D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g -pthread -I$FUNC_INCLUDE"
./thread-create
```

本目录不要使用 `make run`，因为没有 select.c 或 select 目标。

## 当前代码的边界

- `t_join.c` 将 `int*` 强制转为 `void**` 传给 pthread_join。在常见 64 位平台上可能写出 int 的存储范围；不将该程序列为正常运行步骤。正确接收应使用指针大小的对象，再按明确的协议解释返回值。
- `addtwonum.c` 通过整数与指针的转换传回计算结果，依赖平台表示；大输入还可能溢出或耗时很长，练习时使用小的正整数。
- `threadval.c` 通过主线程 sleep 延长参数的存活时间，没有通过 join 明确同步；sleep 不应当作为通用线程同步方式。
- 部分示例用 perror 报告 pthread_create 失败，而 pthread 接口通常直接返回错误码；t_cancel.c 展示了按返回码调用 strerror 的方式。

## 练习目标

- 区分进程 ID 与线程 ID，说明线程间共享地址空间。
- 理解传入结构体地址时的生命周期要求。
- 区分工作线程 return、join 回收与 cancel 请求，理解取消点和清理处理函数。
- 识别返回值类型、整数范围和错误报告方式对线程代码正确性的影响。
