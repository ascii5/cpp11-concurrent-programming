#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

// 线程同步对象
mutex mtx;
condition_variable cv_reader, cv_writer;

// 资源标志
int reader_count = 0;
bool writing = false;

void reader(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv_reader.wait(lock, []{ return !writing; });
        reader_count++;
        if (reader_count == 1) {
            cv_writer.wait(lock, []{ return !writing; });
        }
        lock.unlock();

        cout << "Reader " << id << " starts reading" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Reader " << id << " finishes reading" << endl;

        lock.lock();
        reader_count--;
        if (reader_count == 0) {
            cv_writer.notify_one();
        }
        lock.unlock();

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void writer(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv_writer.wait(lock, []{ return reader_count == 0 && !writing; });
        writing = true;
        lock.unlock();

        cout << "Writer " << id << " starts writing" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Writer " << id << " finishes writing" << endl;

        lock.lock();
        writing = false;
        cv_reader.notify_all();
        cv_writer.notify_one();
        lock.unlock();

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {
    thread t1(reader, 1);
    thread t2(reader, 2);
    thread t3(writer, 1);
    thread t4(writer, 2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}