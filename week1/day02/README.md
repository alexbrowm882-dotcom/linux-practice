# Day02：工作目录与目录操作

## 学习主题与知识点

学习获取当前工作目录、遍历目录、创建目录和删除空目录。重点理解固定缓冲区与动态分配、目录流生命周期、八进制权限、命令行参数校验，以及通过返回值和 `errno` 区分正常结束与错误。

## 文件说明

| 文件 | 作用 |
| --- | --- |
| `getcwd_demo.c` | 用 1024 字节的栈缓冲区获取当前目录。 |
| `getcwd-Dynamic.c` | 用 `getcwd(NULL, 0)` 动态分配路径缓冲区，使用后 `free`；这是 GNU 扩展用法。 |
| `ls.c` | `opendir/readdir/closedir` 遍历指定目录，跳过 `.` 和 `..`，检查读取错误。 |
| `mkdir.c` | 接收目录名和八进制权限，使用 `strtol` 校验后调用 `mkdir`。 |
| `rmdir.c` | 删除指定空目录，失败时报告原因。 |
| `chdir.c` | 当前为空文件，尚未实现切换目录功能，不能独立链接为程序。 |
| `sandbox/nonempty/test.txt` | 用于观察非空目录删除失败的测试文件。 |
| 无扩展名的程序文件 | 仓库中已有的编译产物；下面将程序重新编译到临时目录。 |

## 编译与运行

使用 Linux 或 WSL 的 Linux 终端，并安装 GCC。本目录没有 Makefile。以下命令从本目录执行：

```bash
build=$(mktemp -d)
gcc -Wall -Wextra -g getcwd_demo.c -o "$build/getcwd_demo"
gcc -Wall -Wextra -g getcwd-Dynamic.c -o "$build/getcwd-Dynamic"
gcc -Wall -Wextra -g ls.c -o "$build/my_ls"
gcc -Wall -Wextra -g mkdir.c -o "$build/my_mkdir"
gcc -Wall -Wextra -g rmdir.c -o "$build/my_rmdir"

"$build/getcwd_demo"
"$build/getcwd-Dynamic"
"$build/my_ls" .
"$build/my_mkdir" "$build/empty" 755
"$build/my_rmdir" "$build/empty"
"$build/my_rmdir" sandbox/nonempty  # 预期失败：目录非空
```

实际目录权限还会受进程 `umask` 影响。不要将空的 `chdir.c` 纳入批量可执行程序编译。

## 练习目标

- 能说明两种 `getcwd` 用法的内存管理区别。
- 能完成目录遍历，并正确区分 `readdir` 的结束和失败。
- 能解释权限参数为何按八进制解析，并验证非法权限、目录不存在、目录非空等错误分支。
- 后续可独立补充 `chdir` 练习；当前目录尚未包含该实现。
