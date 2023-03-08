#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex forks[5]; // 五个叉子
condition_variable cv[5]; // 五个条件变量

void philosopher(int id) { 
    int left = id; 
    int right = (id + 1) % 5; 

    while (true) {
        unique_lock<mutex> l(forks[left]); // 左叉子上锁
        unique_lock<mutex> r(forks[right]); // 右叉子上锁
        
        cout << "Philosopher " << id << " is eating." << endl; 
        
        // 模拟吃饭的时间
        this_thread::sleep_for(chrono::milliseconds(500)); 
        
        // 吃完后放下叉子，通知左右两边的哲学家
        cv[left].notify_one(); 
        cv[right].notify_one();
        
        cout << "Philosopher " << id << " is thinking." << endl;
        
        // 模拟思考的时间
        this_thread::sleep_for(chrono::milliseconds(500));
        
        // 如果左边或右边的叉子被占用，则等待
        cv[left].wait(l, [=]() { return !forks[left].try_lock(); }); 
        cv[right].wait(r, [=]() { return !forks[right].try_lock(); });
    }
}

int main() {
    thread philosophers[5];
    
    // 创建五个哲学家
    for(int i = 0; i < 5; ++i){
        philosophers[i] = thread(philosopher, i);
    }
    
    // 等待五个哲学家结束
    for(int i = 0; i < 5; ++i){
        philosophers[i].join();
    }

    return 0;
}