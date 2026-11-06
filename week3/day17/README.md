# Day17：TCP 双向通信与 select 多路复用

## 学习主题与知识点

从按固定顺序收发的 TCP 通信，过渡到使用 select 同时监听终端输入与网络数据。练习描述符集合重建、就绪判断，以及 recv 返回 0 时的连接关闭处理。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `Serve.c` | 接受一个连接后循环先 recv，再从服务端终端读入回复并 send。 |
| `client.c` | 循环先读终端输入并 send，再 recv 服务端回复，与 Serve 配对。 |
| `selectserver.c` | accept 一个连接后，用 select 同时监听标准输入和该连接。 |
| `selectclient.c` | 用 select 同时监听标准输入和已连接套接字。 |
| `Makefile` | 每个 C 文件独立编译；run 指向不存在的 select，并不是 selectserver。 |
| 无扩展名程序 | 仓库已有编译产物。 |

所有网络程序均固定使用 192.168.114.128:8080，没有命令行地址参数。selectserver 仍只 accept 一次，当前不是同时服务多个客户端的服务器。

## 编译与运行

使用 Linux、GCC、GNU Make。自定义 `<func.h>` 未随仓库提供，需要先准备原学习环境的头文件及网络/select 相关声明。从本目录执行：

```bash
export FUNC_INCLUDE=/absolute/path/to/headers
build=$(mktemp -d)
for src in *.c; do
    gcc -D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g \
        -I"$FUNC_INCLUDE" "$src" -o "$build/${src%.c}" || break
done
```

也可用原 Makefile 强制重编译，但会覆盖当前目录的同名编译产物：

```bash
make -B CFLAGS="-D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g -I$FUNC_INCLUDE"
```

不要使用 `make run`。服务端必须已有 192.168.114.128 地址，客户端必须能访问该地址，且 TCP 8080 可用；条件不满足时不能直接复现。本次仅记录当前地址配置，不修改源码。

满足条件后，用两个终端运行一组程序，`build` 均设为编译输出的绝对路径：

```bash
# 终端 1
"$build/Serve"
# 终端 2
"$build/client"
```

先在客户端输入，再在服务端输入回复，观察按轮次交互。结束这一组后，再运行 select 版本：

```bash
# 终端 1
"$build/selectserver"
# 终端 2
"$build/selectclient"
```

select 版本可在任一端输入。可用 Ctrl+C 结束；不要同时运行两组服务端，以免占用同一地址和端口。程序没有设置 SO_REUSEADDR，重启时可能需要等待端口释放。

## 当前代码的边界

- 原始 Serve/client 使用固定顺序的阻塞读写，等待输入或回复时不会处理另一来源。
- select 版本处理了网络 EOF，但没有完整检查 select/read/recv/send 的错误，也没有处理标准输入 EOF。
- 收发使用固定缓冲区长度，没有根据实际读到的字节数发送；字符串结束符、短收发、TCP 消息边界也未完整处理，长消息可能显示异常。
- 当前示例用于理解基本流程，不能据此认为已实现可靠聊天协议或多客户端管理。

## 练习目标

- 比较顺序阻塞收发与基于就绪事件的收发流程。
- 理解每轮 FD_ZERO、FD_SET、FD_ISSET 和 select 的最大描述符加一参数。
- 能说明 recv 返回 0 与错误返回值的区别。
- 识别后续练习方向：输入 EOF、实际字节数、断线清理、消息边界和多连接管理。
