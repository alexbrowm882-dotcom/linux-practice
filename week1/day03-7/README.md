# Day03–7：文件描述符与文件 I/O

## 学习主题与知识点

通过 Linux 文件系统调用学习打开、读取、写入、追加、复制、定位、截断、同步和查询文件属性。重点是打开标志、文件偏移量、短写处理，以及多个描述符共享同一打开文件描述的行为。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `open.c` | 接收文件名，以 `O_RDWR | O_CREAT | O_TRUNC` 打开，打印描述符；已有内容会被清空。 |
| `write.c` | 清空或创建 `hello.txt`，写入 `Hello world\n`。 |
| `read.c` | 从 `hello.txt` 读取最多 1023 字节，补字符串结束符后输出。 |
| `append.c` | 用 `O_APPEND` 向 `hello.txt` 末尾追加一行。 |
| `copy.c` | 接收源和目标路径，循环读取并处理短写；目标使用 `O_TRUNC`。 |
| `lseek.c` | 创建 `position.txt`，将偏移 3 起的三个字符改为 XYZ，再读回。 |
| `dup.c` | 复制描述符，依次写入 ABC、DEF 到 `dup.txt`，观察共享偏移量。 |
| `ftruncate.c` | 向 `cut.txt` 写入十字节后截断为五字节。 |
| `fsync.c` | 向 `sync.txt` 写入内容并调用 `fsync`。 |
| `fstat.c` | 接收文件名，打印文件大小、inode、权限和硬链接数。 |
| `*.txt`、无扩展名程序 | 已有样例数据及编译产物；运行示例会创建或改写同名数据文件。 |

## 编译与运行

使用 Linux、GCC。本目录没有 Makefile。所有 C 文件依赖自定义 `<func.h>`，仓库没有提供该头文件；它不是系统标准头文件。请先准备原学习环境使用的 `func.h` 及其依赖，确认它包含代码所用的标准声明；仅安装 GCC 无法补齐该依赖。

从本目录执行，将 `FUNC_INCLUDE` 改为该头文件所在目录：

```bash
export FUNC_INCLUDE=/absolute/path/to/headers
build=$(mktemp -d)
for src in *.c; do
    gcc -D_GNU_SOURCE -std=gnu11 -Wall -Wextra -g \
        -I"$FUNC_INCLUDE" "$src" -o "$build/${src%.c}" || break
done
```

编译成功后在临时目录运行，避免改写仓库已有的样例数据：

```bash
cd "$build"
./open scratch.txt
./write
./read
./append
./read
./copy hello.txt copied.txt
cmp hello.txt copied.txt
./lseek
./dup
cat dup.txt
./ftruncate
wc -c cut.txt
./fsync
./fstat sync.txt
```

预期：`lseek` 输出的内容为 `abcXYZghij`，`dup.txt` 为 `ABCDEF`，`cut.txt` 为 5 字节。`write` 和 `append` 当前即使正常执行也返回 1，不能仅据退出码认定写入失败，也不要用 `&&` 串联它们。

## 练习目标

- 区分 `O_TRUNC` 与 `O_APPEND`，解释 `lseek`、`dup` 对偏移量的影响。
- 理解 read/write 的实际返回字节数，以及复制程序中的短写循环。
- 观察截断、文件属性和同步调用的结果。
- 识别当前实现的边界：`copy.c` 只比较路径字符串，不能识别硬链接或不同路径指向同一文件；只对独立测试文件操作。
