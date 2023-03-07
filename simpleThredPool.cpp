#include<functional>
#include<stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
class ThreadPool{
public:
    ThreadPool(int num):stop(false){
        for(int i = 0;i < num;++i){
            workers.emplace_back([this]{
                for(;;){
                    function<void()>task;
                    {
                        unique_lock<mutex>lock(mMutex);
                        this -> condtion.wait(lock,[this]{
                            return this -> stop || !tasks.empty();
                        });
                        if(this->stop && tasks.empty()){
                            return;
                        }
                        task = tasks.front();
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    void enqueue(function<void()> task){
        {
            unique_lock<mutex>lock(mMutex);
            tasks.emplace(task);
        }
        condtion.notify_one();
    }
    ~ThreadPool(){
        {
            unique_lock<mutex>lock(mMutex);
            stop = true;
        }
        condtion.notify_all();
        for(thread& i: workers){
            i.join();
        }
    }
private:
    vector<thread>workers;
    condition_variable condtion;
    queue<function<void()>>tasks;
    mutex mMutex;
    bool stop;
};
void task1()
{
    cout << "task1 is already!" << endl;
}
void task2()
{
    cout << "task2 is already!" << endl;
}
void task3()
{
    cout << "task3 is already!" << endl;
}
int main()
{
    ThreadPool pool(3);
    pool.enqueue(task1);
    pool.enqueue(task2);
    pool.enqueue(task3);
    pool.enqueue(task1);
    pool.~ThreadPool();
    this_thread::sleep_for(chrono::milliseconds(100));
    system("pause");
    return 0;
}
