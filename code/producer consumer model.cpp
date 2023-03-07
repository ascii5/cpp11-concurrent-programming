#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

const int BUFFER_SIZE = 10;
queue<int> buffer;

mutex mtx;
condition_variable produce_cv;
condition_variable consume_cv;

void producer() {
    for (int i = 1; i <= 20; i++) {
        {
            unique_lock<mutex> lck(mtx);
            produce_cv.wait(lck, []{ return buffer.size() < BUFFER_SIZE; });
            buffer.push(i);
            cout << "Producer produced " << i << endl;
        }
        consume_cv.notify_one();
    }
}

void consumer() {
    while (true) {
        {
            unique_lock<mutex> lck(mtx);
            consume_cv.wait(lck, []{ return buffer.size() > 0; });
            int val = buffer.front();
            buffer.pop();
            cout << "Consumer consumed " << val << endl;
        }
        produce_cv.notify_one();
    }
}

int main() {
    thread producer_thread(producer);
    thread consumer_thread(consumer);
    producer_thread.join();
    consumer_thread.join();
    return 0;
}