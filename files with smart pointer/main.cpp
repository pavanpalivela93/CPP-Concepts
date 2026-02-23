// /Users/pavanpalivela/Downloads/Kranthi_Resume_CPP_Updated.pdf
#include <iostream>

class File
{
    const std::string path;
    FILE *f = nullptr;

public:
    File(const std::string _path) : path(_path)
    {
        std::cout << "file opening: " << f << std::endl;
        f = fopen(path.c_str(), "r");
        std::cout << "file opened: " << f << std::endl;
    }

    int FileClose()
    {
        std::cout << "file closing: " << f << std::endl;
        int res = fclose(f);
        if (res == 0)
            f = nullptr;
        std::cout << "file closed: " << f << std::endl;
        return res;
    }

    FILE *getFilePtr()
    {
        return f;
    }

    ~File()
    {
        FileClose();
    }
};

int main()
{
    File file1("/Users/pavanpalivela/Downloads/Kranthi_Resume_CPP_Updated.pdf"); // custome file class to manage close on out of scope
    if (!file1.getFilePtr())
        return 0;

    std::unique_ptr<FILE, decltype(&fclose)>
        file(fopen("/Users/pavanpalivela/Downloads/Kranthi_Resume_CPP_Updated.pdf", "r"), &fclose); // unique pointer when goes out of scope by calling the custome deleter fclose given
    // while destructing unique ptr file file.~unique_ptr() -> deleter(ptr); -> fclose(ptr);
    // equalant to
    // FILE* f = fopen("test.txt", "r");
    // if (!f) return;
    // fclose(f);  // must remember manually

    if (!file)
        return 0;

    // use file.get()

    return 0;
}