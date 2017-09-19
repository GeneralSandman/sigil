# **sigil**

***
******
--------

> # 1.数据库的基本操作
- 显示所有数据库
```
dbs
```
- 显示当前数据库
```
db
```
- 选择数据库
```
select <db>
```
- 增加数据库
```
createdb <db>
createdb <db1> <db2>
```
- 删除数据库

```
deletedb <db>
deletedb <db1> <db2>
```

- 持久化
```
save
bgsave
```

- 退出sigil
```
quit
Ctrl-c(增加了信号处理)
```

- 获取上一条/下一条命令：```↑ ↓```

- history命令
    - ```history```：获取本次开启服务所有执行命令 
    - ```history n```：获取本次开启服务前n条命令
    - ```history -n```：最后n条命令
    - ```history -c```：清除本次缓存中的所有命令，并写入文件中
    - ```history -w```：保存命名到本地文件中，用于恢复


- 帮助命令：```help```

> # 2.列表(list)

> 列表按照插入顺序排列,如果列表不存在，push操作会创建一个新列表，而其他命令会报错；但是llen不会创建一个新列表，也不会报错，只是返回零。



- 获取所有元素
```
lmem key
```

- 在key的头部插入值
```
lpush key value1 [value2]
```
- 在key的尾部插入值
```
rpush key value1 [value2]
```

- 弹出并获取列表的第一个元素
```
lpop key
```
- 弹出并获取列表的最后一个元素
```
rpop key
```

- 获取列表的长度
```
llen key
```

- 通过索引获取列表中的元素
```
lindex key index
```
- 通过索引设置列表中的元素
```
lindex key index value
```
- 在列表元素前/后插入新元素
```
linsert key before|after pro_value new_value
```
- 获取指定区间的元素[begin,end)
```
lrange key begin end
```
- 移除指定元素
```
lrem key value
```
- 清空列表
```
lclear key
```

># 3.哈希(Hash)


> hash 是一个string类型的field和value的映射表

- 将哈希表key中field的值设为value
```
hset key field value
```

- 获取哈希表key中field的值(存在bug)
```
hget key field
```

- 同时将多个 field-value (域-值)对设置到哈希表 key 中
```
hmset key field1 value1 [field2 value2 ]
```
- 同时获取哈希表key中的多个field的值(存在bug)
```
hmget key field1 [field2]
```
- 获取字段数量
```
hlen key
```

- 清空哈希表
```
hclear key
```

># 4.集合（Set）

- 向集合添加一个或多个成员
```
sadd key value1 [value2] 
```

- 移除并返回集合中的一个随机元素
```
spop key
```

- 移除指定value的元素
```
srem key
```

- 获取集合的元素数量
```
scard key
```

- 获取集合所有元素
```
smem key
```
- 判断value是否存在于set集合
```
sismem key value
```
- 返回两个集合的交集
```
sinter key1 key2
```
- 返回两个集合的并集
```
sunion key1 key2
```
- 返回两个集合的差集
```
sdiff key1 key2
```

4	SDIFFSTORE destination key1 [key2] 
返回给定所有集合的差集并存储在 destination 中
6	SINTERSTORE destination key1 [key2] 
返回给定所有集合的交集并存储在 destination 中
9	SMOVE source destination member 
将 member 元素从 source 集合移动到 destination 集合
11	SRANDMEMBER key [count] 
返回集合中一个或多个随机数
14	SUNIONSTORE destination key1 [key2] 
所有给定集合的并集存储在 destination 集合中
15	SSCAN key cursor [MATCH pattern] [COUNT count] 
迭代集合中的元素

># 5.数据库的持久化

------

## 一、日志使用方法（test/test_log.cc）
```
日志采用单例 (Meyers Singleton) 模式
```

### 1.日志的初始化
五个日志等级：Debug,Info,Warning,Error,Fatal

前五个参数指定日志文件，如果参数为"",则日志将在终端输出，最后一个参数为系统日志等级，默认等级为Info
```
void initLogger(const std::string &debug_log_filename,
                const std::string &info_log_filename,
                const std::string &warn_log_filename,
                const std::string &error_log_filename,
                const std::string &fatal_log_filename,
                log_level level);
```

### 2.日志等级改变

```
void setLogLevel(log_level level);
```

### 3.打印日志方法
```
LOG(level)<<information;
```
level 为本条日志级别，information为日志信息

### 4.程序结束时无需释放内存


### 5.注意事项
单条日志级别如果比系统日志等级小，则本条日志将被忽略。

栗：如果当前系统日志等级为Info,则LOG(Debug)无效，其余均有效。



安装readline库
ldconfig -p | grep readline  
显示libreadline.so.6 (libc6,x86-64) => /lib/x86_64-linux-gnu/libreadline.so.6


## 二、各种依赖

### 1.sigil依赖readline库
- [readline安装方法](http://blog.csdn.net/zmrlinux/article/details/47052797)
- 查看动态库
```
ldconfig -p ｜ grep readline
```
显示为
```
libreadline.so.6 (libc6,x86-64) => /lib/x86_64-linux-gnu/libreadline.so.6
libguilereadline-v-18.so.18 (libc6,x86-64) => /usr/lib/x86_64-linux-gnu/libguilereadline-v-18.so.18
libguilereadline-v-18.so (libc6,x86-64) => /usr/lib/x86_64-linux-gnu/libguilereadline-v-18.so
```
- 修改Makefile中readline变量中的动态库改为
```
/usr/lib/x86_64-linux-gnu/libreadline.so
```


配置文件（sigil.conf）
配置文件为[HCNON格式]!()
1.安装解析HCNON依赖

Build Requirements

OSX or Linux
GCC >= 4.8 or Clang >= 3.4 (with libc++)
CMake >= 3.2.2
Boost Libraries >= 1.54
Leatherman

- Building Leatherman
```
git clone https://github.com/puppetlabs/leatherman
cd leatherman
mkdir build
cd build
cmake ..
make
sudo make install
```

- Pre-Build

```
git clone https://github.com/puppetlabs/cpp-hocon
cd cpp-hocon
mkdir release
cd release
cmake ..

mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..

cd ../release
make
make install

make test


```