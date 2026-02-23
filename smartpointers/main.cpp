#include <iostream>
#include <memory>

class Entity
{
public:
    std::string value;
    explicit Entity(std::string _value) : value(_value)
    {
        // std::cout << "value:" << value << std::endl;
        // std::cout << "constructor called" << std::endl;
    }

    Entity(Entity &&entity) noexcept : value(std::move(entity.value))
    {
        // std::cout << "value:" << value << std::endl;
        //::cout << "move constructor called" << std::endl;
    }

    Entity &operator=(Entity &&entity) noexcept
    {
        if (this != &entity)
        {
            this->value = std::move(entity.value);
        }
        return *this;
    }

    Entity(const Entity &entity) : value(entity.value)
    {
        // std::cout << "value:" << value << std::endl;
        // std::cout << "copy constructor called" << std::endl;
    }

    Entity &operator=(const Entity &entity)
    {
        if (this != &entity)
        {
            this->value = entity.value;
        }
        return *this;
    }

    ~Entity()
    {
        // std::cout << "value:" << value << std::endl;
        // std::cout << "destructor called" << std::endl;
    }
};

struct Manager
{
    std::shared_ptr<Entity> obj;
};
struct B;
struct A
{
    std::shared_ptr<B> bPtr;
    ~A()
    {
        std::cout << "A destructor called" << std::endl;
    }
};

struct B
{
    std::weak_ptr<A> aPtr;
    ~B()
    {
        std::cout << "B destructor called" << std::endl;
    }

    void use_weak_ptr()
    {
        if (std::shared_ptr<A> temp = aPtr.lock()) // also can use aPtr.use_count() or aPtr.expired()
        {
            std::cout << "is alive" << std::endl;
        }
        else
        {
            std::cout << "is dead" << std::endl;
        }
    }
};

int main()
{
    {
        //--------------------------------------
        // std::unique_ptr

        // std::unique_ptr<Entity> entity = new Entity(); // cannot do this because unique pointer constructor is explicit and need to be call as below
        // std::unique_ptr<Entity> entity(new Entity()); // can do this but for ✅ Exception safe ✅ Cleaner ❌ Avoids temporary raw pointer use make_unique
        std::unique_ptr<Entity> uniqueEntity = std::make_unique<Entity>(std::string("uniqueEntity"));
        // std::unique_ptr<Entity> e1 = entity; // ❌ compile error unique pointer copy constructor and assignment is deleted in its class and hence we cannot copy but we can move the ownership
        std::unique_ptr<Entity> uniqueEntity1 = std::move(uniqueEntity); // moving pointer not object hence move in unique_ptr gets called
        Entity e2 = std::move(*uniqueEntity1);                           // moving object itself not pointer hence move in entity called

        std::cout << std::endl;
        // 🔹 When to Use unique_ptr
        // ✔ Default smart pointer
        // ✔ Single ownership
        // ✔ Resource wrapper
        // ✔ High performance (no ref counting overhead)
        // Cost: same as raw pointer.

        //--------------------------------------
        // std::shared_ptr

        // Memory Layout
        // shared_ptr ─┐
        // shared_ptr ─┼──► Control Block ─► Object
        // shared_ptr ─┘

        // Control block contains:
        //  strong count
        //  weak count
        //  deleter
        //  allocator

        // template<typename T, typename Alloc>
        // struct control_block {
        //     std::atomic<long> strong_count;
        //     std::atomic<long> weak_count;
        //     Alloc allocator;     // stored allocator
        //     T object;            // managed object

        std::shared_ptr<Entity> sharedEntity1 = std::make_shared<Entity>(std::string("sharedEntity1"));
        std::cout << "sharedEntity1 count: " << sharedEntity1.use_count() << std::endl;
        {
            std::shared_ptr<Entity> sharedEntity2 = sharedEntity1;
            std::cout << "sharedEntity1 count: " << sharedEntity1.use_count() << std::endl;
            std::cout << "sharedEntity2 count: " << sharedEntity2.use_count() << std::endl;
        }
        std::cout << "sharedEntity1 count: " << sharedEntity1.use_count() << std::endl;
        std::cout << std::endl;

        std::shared_ptr<Entity> sEntity = std::make_shared<Entity>(std::string("Manager"));
        std::cout << "sharedManager count: " << sEntity.use_count() << std::endl;
        {
            Manager man;
            man.obj = sEntity;
            std::cout << "Manager count: " << man.obj.use_count() << std::endl;
        }
        std::cout << "sharedManager count: " << sEntity.use_count() << std::endl;
        std::cout << std::endl;

        // shared ptr problem 1
        Entity *temp;
        std::cout << "sharedEntity1 count: " << sharedEntity1.use_count() << std::endl;
        {
            std::shared_ptr<Entity> sharedtemp = std::make_shared<Entity>(std::string("sharedtemp"));
            // (*sharedtemp).value or sharedtemp->value
            temp = &(*sharedtemp);
            std::cout << "temp value: " << temp->value << std::endl;
        }
        std::cout << "temp value: " << temp->value << std::endl; // ❌ now temp is a dangling pointer
        std::cout << std::endl;

        // Cyclic Reference Problem
        // weak pointers
        std::shared_ptr<B> b = std::make_shared<B>();
        {
            std::shared_ptr<A> a = std::make_shared<A>();

            a->bPtr = b;
            b->aPtr = a;
            b->use_weak_ptr();
        }
        b->use_weak_ptr();

        // as both holds each other as both are sared pointers in class members the shared count will be 1 even after a,b destroyed but A::b & B::a still there and keep each other alive
        // to fix this wee need to make one of them to weak pointer

        return 0;
    };
}