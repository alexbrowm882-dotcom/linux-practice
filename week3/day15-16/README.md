# Day15–16：字节序、IPv4 地址与 TCP 连接入门

## 学习主题与知识点

学习主机字节序与网络字节序转换、IPv4 文本与二进制地址转换，认识 sockaddr_in，并依次实践 socket、bind、listen、accept、connect、send 和 recv。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `socketbiglittleconversion.c` | 演示 htons/ntohs、htonl/ntohl，并查看网络序数据的内存字节。 |
| `iptoaddr.c` | 读取 IPv4 文本，用 inet_aton、inet_ntoa 及 htonl/ntohl 转换。 |
| `serve.c` | 创建套接字并绑定 192.168.106.130:8080，成功后关闭；不监听或接收连接。 |
| `Serve.c` | 在 192.168.114.128:8080 监听，接受一个连接并接收一次消息。 |
| `client.c` | 连接 192.168.114.128:8080，发送五字节 hello。 |
| `Makefile` | 每个 C 文件独立生成同名程序；run 指向本目录不存在的 select。 |
| 无扩展名程序 | 已有编译产物。 |

`Serve.c` 与 `serve.c` 是不同文件，应在区分大小写的 Linux 文件系统中检出和编译；WSL 可使用其 Linux 主目录。大小写不敏感的 Windows 目录可能无法同时保存它们。

## 编译与运行

使用 Linux、GCC、GNU Make。所有源码依赖仓库未附带的自定义 `<func.h>`，先准备原学习环境的头文件及相关网络声明。从本目录编译到临时目录：

```bash
export FUNC_INCLUDE=/absolute/path/to/headers
build=$(mktemp -d)
for src in *.c; do
    gcc -D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g \
        -I"$FUNC_INCLUDE" "$src" -o "$build/${src%.c}" || break
done
"$build/socketbiglittleconversion"
printf '127.0.0.1\n' | "$build/iptoaddr"
```

若使用原 Makefile，可运行下面命令强制重编译；它会覆盖本目录同名编译产物：

```bash
make -B CFLAGS="-D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g -I$FUNC_INCLUDE"
```

不要使用 `make run`。网络示例没有命令行 IP/端口参数：运行 `serve` 要求本机已有 192.168.106.130；运行 `Serve` 要求服务端已有 192.168.114.128，客户端能访问该地址，且 TCP 8080 可用。地址不满足时不能直接复现，本次文档不改变源码中的 IP。

在满足上述网络条件的原实验环境中，用两个终端运行：

```bash
# 服务端终端，build 为编译输出的绝对路径
"$build/Serve"

# 客户端终端，设置为同一构建目录的绝对路径
"$build/client"
```

服务端预期显示 hello 后结束。`serve` 仅用于单独观察 bind 成功，不是 client 的配对服务端。

## 练习目标

- 能区分数值显示与内存字节排列，解释网络字节序采用大端的含义。
- 能完成 IPv4 文本和地址结构之间的转换，区分 IP 转换与端口转换。
- 能说明监听套接字与 accept 返回的连接套接字的区别。
- 理解当前 TCP 代码仅演示一次连接和消息交换；Serve/client 缺少完整返回值检查与资源清理，没有处理短收发和消息边界。
