#include <filesystem>
#include <iostream>
#include <string>
#include <stdexcept>

namespace fs = std::filesystem;

class FilePath {
private:
    fs::path Searching_Path;
    fs::path Destination_Path;

public:
    FilePath(const std::string& src, const std::string& dst)
        : Searching_Path(src), Destination_Path(dst) {}

    void CopyFiles() {
        try {
            if (!fs::exists(Searching_Path)) {
                throw std::runtime_error("Source path does not exist");
            }

            for (const auto& file : fs::directory_iterator(Searching_Path)) {
                if (fs::is_regular_file(file)) {
                    fs::path SourceFile = file.path();
                    fs::path Destination = Destination_Path / SourceFile.filename();

                    fs::copy(SourceFile, Destination, fs::copy_options::overwrite_existing);
                    std::cout << "File copied: " << SourceFile.filename() << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error occurred: " << e.what() << std::endl;
        }
    }
};

int main() {
    try {
        FilePath backup("Your/path/here", "And/here");
        backup.CopyFiles();
    }
    catch (const std::exception& e) {
        std::cerr << "Unhandled error: " << e.what() << std::endl;
    }

    return 0;
}
