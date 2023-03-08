#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

using namespace std;

// 线程同步对象
mutex mtx;
condition_variable cv;

// 随机数生成器
default_random_engine generator;
uniform_int_distribution<int> distribution(1, 3);

// 材料标志
bool paper_on_table = false;
bool tobacco_on_table = false;
bool glue_on_table = false;

void smoker_paper() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return (!paper_on_table && tobacco_on_table && glue_on_table); });
        cout << "Smoker with paper starts smoking" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Smoker with paper finishes smoking" << endl;
        tobacco_on_table = false;
		glue_on_table = false;
        cv.notify_all();
    }
}

void smoker_tobacco() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return (!tobacco_on_table && paper_on_table&& glue_on_table); });
        cout << "Smoker with tobacco starts smoking" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Smoker with tobacco finishes smoking" << endl;
        paper_on_table = false;
		glue_on_table = false;
        cv.notify_all();
    }
}

void smoker_glue() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return (!glue_on_table && paper_on_table && tobacco_on_table); });
        cout << "Smoker with glue starts smoking" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Smoker with glue finishes smoking" << endl;
        paper_on_table = false;
		tobacco_on_table = false;
        cv.notify_all();
    }
}

void agent() {
    while (true) {
        unique_lock<mutex> lock(mtx);

        int random_int = distribution(generator);

        if (random_int == 1) {
            paper_on_table = true;
            tobacco_on_table = true;
            cout << "Agent puts paper and tobacco on the table" << endl;
        } else if (random_int == 2) {
            paper_on_table = true;
            glue_on_table = true;
            cout << "Agent puts paper and glue on the table" << endl;
        } else {
            tobacco_on_table = true;
            glue_on_table = true;
            cout << "Agent puts tobacco and glue on the table" << endl;
        }

        cv.notify_all();
        lock.unlock();

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {
    thread t1(smoker_paper);
    thread t2(smoker_tobacco);
    thread t3(smoker_glue);
    thread t4(agent);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}