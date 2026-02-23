#include <unordered_map>

struct PairHash
{
    size_t operator()(const std::pair<int, int> &p) const
    {
        return std::hash<int>()(p.first) ^
               (std::hash<int>()(p.second) << 1);
    }
};

int main()
{
    // Custom Hash Function
    //  unordered_map<pair<int,int>, int>
    std::unordered_map<std::pair<int, int>, int, PairHash> mp;
    mp[{1, 2}] = 5;

    // Controlling Load Factor
    mp.max_load_factor(0.7);
    mp.rehash(100);   // force at least 100 buckets
    mp.reserve(1000); // optimize for 1000 elements

    // 🔥 Always call reserve() when size is known.
    // Avoids multiple rehashes → improves performance.
    return 0;
}