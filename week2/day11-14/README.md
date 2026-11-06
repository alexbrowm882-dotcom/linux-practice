# Day11–14：互斥锁、条件变量、阻塞队列与线程池

## 学习主题与知识点

围绕账户操作和任务队列练习并发同步：用互斥锁保护余额，用不同加锁策略避免死锁，以条件变量构造有界阻塞队列，再由多个工作线程消费任务。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `bank.c` | 10 个线程尝试从余额 100 的账户各取 100，使用账户锁并注册解锁清理函数。 |
| `deadlock.c` | 转账前先持有全局 protection 锁，再取得两把账户锁，串行化取得双锁的阶段。 |
| `deadlock1.c` | 按账户 id 从小到大取得账户锁，统一加锁顺序。 |
| `blockq.h` | 声明容量 1024 的整数循环队列、互斥锁、not_empty/not_full 条件变量及队列接口。 |
| `blockq.c` | 实现创建、销毁、判空、判满、入队、出队与查看队首；条件等待使用 while 重新检查条件。 |
| `pc.c` | 创建 8 个工作线程，投递 100 个任务；每个任务 sleep 3 秒，最后投递 8 个 -1 退出标记并 join。 |
| `Makefile` | 通用单源文件链接规则，不能正确构建需要 blockq.c 的 pc；也会尝试将没有 main 的 blockq.c 链接为程序。 |
| 无扩展名程序 | 仓库已有编译产物。 |

文件名虽然含 deadlock，但当前两个转账示例均实现了规避死锁的策略，不应描述为必然死锁的程序。

## 编译与运行

使用 Linux、GCC、POSIX 线程库。先准备未随仓库提供的自定义 `<func.h>` 及其依赖，包含 pthread、bool 等声明。从本目录执行：

```bash
export FUNC_INCLUDE=/absolute/path/to/headers
build=$(mktemp -d)
for name in bank deadlock deadlock1; do
    gcc -D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g -pthread \
        -I"$FUNC_INCLUDE" "$name.c" -o "$build/$name" || break
done
gcc -D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g -pthread \
    -I"$FUNC_INCLUDE" pc.c blockq.c -o "$build/pc"

"$build/deadlock"
"$build/deadlock1"
"$build/pc"
```

`pc` 通常需约 39 秒处理完任务（受调度影响）；输出顺序由线程调度决定，任务应被消费后各线程读取退出标记并结束。当前 Makefile 不支持上述多文件依赖，不推荐直接 `make all`；`make run` 还指向本目录不存在的 select。

## 当前代码的边界

- `bank.c` 在 pthread_cleanup_push/pop 之间直接 return，绕过了配对的清理宏退出路径，不适合作为可靠的取消清理示范。因此上面只提供其编译步骤，没有将其列为正常运行验证。应先理解配对作用域与统一退出路径，再另行改进实现。
- 账户示例通过 `int` 与 `void*` 转换传递金额，在常见 64 位编译环境中可能出现大小转换警告。
- 队列的 empty/full 查询只返回查询时刻的快照；调用者不能据此假设后续 push/pop 一定不阻塞。
- 线程池通过 -1 结束工作线程，因此 -1 被保留为控制值；销毁队列前先 join 所有工作线程。

## 练习目标

- 能解释余额检查和更新为何应在同一临界区。
- 比较全局保护锁与统一锁顺序的并发程度及死锁规避原理。
- 解释条件等待为何放在 while 中，以及等待时如何释放和重新取得互斥锁。
- 跟踪循环队列的 front、rear、size，理解满队列/空队列上的阻塞与唤醒。
- 理解多文件链接、任务分发、退出标记和线程回收的完整生命周期。
