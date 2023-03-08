# 基于从cpp11的多线程入门实例

## 1.producerconsumermodel

producer consumer model包含了两个函数的设计

- 生产者
- 消费者

------



> 生产者

生产者的职责：

- 检查是否应该阻塞此线程
- 生产任务
- 唤醒消费者线程

> 消费者

消费者的职责：

- 检查是否应该阻塞此线程
- 消费任务
- 唤醒生产者线程

## 2.smokerProblem

smokerProblem 的设计包括了

- 有纸的吸烟者
- 有胶水的吸烟者
- 有烟草的吸烟者
- 生产者

------



>有纸的吸烟者

- 检查条件是否阻塞线程
- 吸烟
- 唤醒其他线程

> 有胶水的吸烟者

- 检查条件是否阻塞线程
- 吸烟
- 唤醒其他线程

> 有烟草的吸烟者

- 检查条件是否阻塞线程
- 吸烟
- 唤醒其他线程

> 生产者

随机生产两种卷烟材料

## 3.writerAndReader

writerAndReader设计了以下函数

- writer
- reader

---



> writer

- 检查条件是否阻塞线程
- 写操作
- 唤醒一个写进程和所有的读进程

> reader

- 检查是否阻塞(writing 为 false)
- 执行读操作，计数reader数量
- 唤醒线程

## 4.philosopher'sProblem

哲学家函数

- 思考
- 竞争条件
- 吃饭
- 释放条件

## simpleThreadPool

threadPool 类包含了三个函数的设计：

- 构造函数
- equeue函数
- 析构函数

------



> 构造函数

![error](https://github.com/ascii5/cpp11-concurrent-programming/blob/main/pictures/threadPool.png)

>queue 函数

![error](https://github.com/ascii5/cpp11-concurrent-programming/blob/main/pictures/ThreadPool1.png)

>析构函数

![error](https://github.com/ascii5/cpp11-concurrent-programming/blob/main/pictures/ThreadPool2.png)

