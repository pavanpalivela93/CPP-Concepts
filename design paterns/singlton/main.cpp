class Singleton
{
private:
    static Singleton *ptr;
    Singleton() = default;

public:
    static Singleton *getInstance()
    {
        if (ptr == nullptr)
        {
            return new Singleton();
        }
        return ptr;
    }
};

Singleton *Singleton::ptr = nullptr;