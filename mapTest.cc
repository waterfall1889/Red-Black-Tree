#include "map.h"
#include <iostream>
#include <stdexcept>

class Test {
private:
    int testSize;
    Map m;
    int successInsert;
    int totalInsert;
    int successSearch;
    int totalSearch;
    int successDelete;
    int totalDelete;

public:
    Test(int s) : testSize(s), successInsert(0), totalInsert(0),
                  successSearch(0), totalSearch(0), successDelete(0), totalDelete(0) {}

    void testInsert();
    void testSearch();
    void testDelete();

    void runTest();
};

void Test::runTest() {
    testInsert();
    testSearch();
    testDelete();
    std::cout << "[Test Results]\n";
    std::cout << "Insert: " << successInsert << "/" << totalInsert << " success\n";
    std::cout << "Search: " << successSearch << "/" << totalSearch << " success\n";
    std::cout << "Delete: " << successDelete << "/" << totalDelete << " success\n";
}

void Test::testInsert() {
    std::cout << "[Insert Test]\n";

    // Phase 1: Normal insert and check if inserted correctly
    for (int i = 0; i < testSize; ++i) {
        uint64_t key = i;
        std::string value = "Value" + std::to_string(i);
        m.insert(key, value);

        // Check if the inserted key-value pair is correct
        std::string retrievedValue = m[key];
        if (retrievedValue == value) {
            successInsert++;
        }
        else {
            std::cerr << "Insert failed for key: " << key << ". Expected: " << value << ", Got: " << retrievedValue << "\n";
        }
        totalInsert++;
    }

    // Phase 2: Update existing keys and check if updated correctly
    for (int i = 0; i < testSize; ++i) {
        uint64_t key = i;
        std::string updatedValue = "UpdatedValue" + std::to_string(i);
        m.insert(key, updatedValue);  // Assuming insert allows updating

        // Check if the updated key-value pair is correct
        std::string retrievedValue = m[key];
        if (retrievedValue == updatedValue) {
            successInsert++;
        }
        else {
            std::cerr << "Insert (update) failed for key: " << key << ". Expected: " << updatedValue << ", Got: " << retrievedValue << "\n";
        }
        totalInsert++;
    }
}

void Test::testSearch() {
    std::cout << "[Search Test]\n";

    // Phase 1: Search for existing keys
    for (int i = 0; i < testSize; ++i) {
        uint64_t key = i;
        std::string expectedValue = "UpdatedValue" + std::to_string(i);
        std::string value = m[key];  // Search for the existing key

        if (value == expectedValue) {
            successSearch++;
        } else {
            std::cerr << "Search failed for key: " << key << ". Expected: " << expectedValue << ", Got: " << value << "\n";
        }
        totalSearch++;
    }

    // Phase 2: Search for unknown keys (no error handling, just return empty string)
    for (int i = testSize; i < testSize + 5; ++i) {
        uint64_t key = i;  // Try searching for a non-existing key
        std::string value = m[key];

        if (value.empty()) {  // Correct behavior, return empty string for non-existent key
            successSearch++;
        } else {
            std::cerr << "Unexpectedly found value for non-existent key: " << key << "\n";
        }
        totalSearch++;
    }
}

void Test::testDelete() {
    std::cout << "[Delete Test]\n";

    // Phase 1: Delete the existing keys and check if they're deleted
    for (int i = 0; i < testSize; ++i) {
        uint64_t key = i;
        if(m.remove(key)){
            successDelete++;
        }  // Try to delete the key
        totalDelete++;
    }

    // Phase 2: Try to delete non-existing keys and check if the deletion fails (returns false)
    for (int i = testSize; i < testSize + 5; ++i) {
        uint64_t key = i;  // Try deleting a non-existent key
        bool deleted = m.remove(key);
        if (deleted) {
            std::cerr << "Unexpectedly deleted non-existent key: " << key << "\n";
        } else {
            successDelete++;  // Correct behavior, non-existent key was not deleted
        }
        totalDelete++;
    }
}

int main() {
    Test test(100);  // Example with 10 test cases
    test.runTest();
    return 0;
}
