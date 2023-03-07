# 基于从cpp11的多线程入门实例

## contain

### producer consumer model

producer consumer model包含了两个函数的设计

- 生产者
- 消费者

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

### simple ThreadPool

threadPool 类包含了三个函数的设计：

- 构造函数
- equeue函数
- 析构函数

> 构造函数

![error](C:\Users\user\Desktop\cpp11-concurrent-programming\pictures\threadPool.png)

>queue 函数

![error](C:\Users\user\Desktop\cpp11-concurrent-programming\pictures\ThreadPool1.png)

>析构函数

![error](C:\Users\user\Desktop\cpp11-concurrent-programming\pictures\ThreadPool2.png)

