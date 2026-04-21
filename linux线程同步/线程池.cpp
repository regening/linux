#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>
#include <string>
#include <functional>

using namespace std;

struct Task {
    function<void()> func;  
};

class ThreadPool {
private:
    vector<thread> workers;
    queue<Task> tasks;
    mutex queue_mutex;
    condition_variable cond_var;
    bool stop;

public:
    ThreadPool(int numThreads = 4) : stop(false) {
        for (int i = 0; i < numThreads; ++i) {
            workers.emplace_back([this]() {
                while (true) {
                    Task task;
                    {
                        unique_lock<mutex> lock(this->queue_mutex);
                        this->cond_var.wait(lock, [this]() { return stop || !tasks.empty(); });
                        if (stop && tasks.empty())
                            return;
                        task = tasks.front();
                        tasks.pop();
                    }
                    task.func(); // 执行任务
                }
            });
        }
    }

    void addTask(function<void()> func) {
        {
            unique_lock<mutex> lock(queue_mutex);
            tasks.push(Task{func});
        }
        cond_var.notify_one();
    }

    void shutdown() {
        {
            unique_lock<mutex> lock(queue_mutex);
            stop = true;
        }
        cond_var.notify_all();
        for (thread &t : workers)
            t.join();
    }

    ~ThreadPool() {
        if (!stop) shutdown();
    }
};

// 矩阵阶乘任务
void computeFactorial(int n) {
    long result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;
    cout << "线程 " << this_thread::get_id() << " 计算 " << n << " 的阶乘 = " << result << endl;
}

// 下载任务
void downloadFile(string url, string path) {
    cout << "线程 " << this_thread::get_id() << " 下载文件 " << url << " 到 " << path << endl;
    this_thread::sleep_for(chrono::seconds(2)); // 模拟下载耗时
    cout << "线程 " << this_thread::get_id() << " 下载完成: " << path << endl;
}

int main() {
    ThreadPool pool(4); 

    // 矩阵任务 
    vector<int> nums = {5, 6, 7, 8, 9};
    for (int n : nums) {
        pool.addTask([n]() { computeFactorial(n); });
    }

    // 下载任务
    vector<pair<string,string>> files = {
        {"http://example.com/file1", "file1.txt"},
        {"http://example.com/file2", "file2.txt"},
        {"http://example.com/file3", "file3.txt"}
    };
    for (auto &f : files) {
        pool.addTask([f]() { downloadFile(f.first, f.second); });
    }

    this_thread::sleep_for(chrono::seconds(10));

    pool.shutdown();
    cout << "线程池已关闭" << endl;

    return 0;
}