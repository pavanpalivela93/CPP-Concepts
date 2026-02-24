template <typename T>
class vector
{
private:
    T *data_;         // pointer to heap memory
    size_t size_;     // number of constructed elements
    size_t capacity_; // allocated memory

public:
    vector()
        : data_(nullptr), size_(0), capacity_(0) {}

    ~vector()
    {
        clear();
        operator delete(data_);
    }

    void push_back(const T &value)
    {
        if (size_ == capacity_)
            reallocate();

        new (data_ + size_) T(value); // placement new
        ++size_;
    }
};