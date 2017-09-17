# sigil


hset myhash field1 "Hello" field2 "World"

hget myhash field1

# >1.数据库的基本操作
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

- 退出sigil

```
quit
Ctrl-c(增加了信号处理)
```

> # 2.列表(list)

> 列表按照插入顺序排列,如果列表不存在，push操作会创建一个新列表，而其他命令会报错；但是llen不会创建一个新列表，也不会报错，只是返回零。

|命令|操作|
|:-------:|:-------:|
|LPUSH key value1 [value2] |在key的头部插入值|

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

># 4.数据库的持久化

---

## 日志使用方法（test/test_log.cc）
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


### 3.注意事项
单条日志级别如果比系统日志等级小，则本条日志将被忽略。

栗：如果当前系统日志等级为Info,则LOG(Debug)无效，其余均有效。
