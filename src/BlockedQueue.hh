#ifndef BLOCKEDQUEUE
#define BLOCKEDQUEUE
#include <queue>
#include <mutex>

using namespace std;
template <typename T>
class BlockedQueue
{
public:
    BlockedQueue() : stop_(false) {}
    void push(T const &value)
    {
        if (stop_)
            return;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(value);
        }
        condition_.notify_one();
    }

    bool pop(T &value)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (true)
        {
            if (queue_.empty())
            {
                if (stop_)
                    return false;
            }
            else
                break;
            condition_.wait(lock);
        }
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    void start()
    {
        if (!stop_)
            return;
        stop_ = false;
    }

    void stop()
    {
        if (stop_)
            return;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            stop_ = true;
        }
        condition_.notify_all();
    }

    void clear()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (!queue_.empty())
        {
            queue_.pop();
        }
    }

    size_t size() const
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    std::condition_variable condition_;
    std::queue<T> queue_;
    std::atomic_bool stop_;
    mutable std::mutex mutex_;
};
#endif