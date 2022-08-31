#include <iostream>
#include <vector>

typedef struct Item {
    unsigned long int key;
    unsigned long int value;
} Item;

unsigned long int GetMaxKey(std::vector<Item>& inArr)
{
    unsigned long int mx = inArr[0].key;
    for (int i = 1; i < inArr.size(); i++)
        if (inArr[i].key > mx)
            mx = inArr[i].key;
    return mx;
}

void CountSort(std::vector<Item>& inArr, int exp)
{
    std::vector<Item> outArr(inArr.size());
    std::vector<int> count(10, 0);
    for (int i = 0; i < inArr.size(); ++i) {
        ++count[(inArr[i].key / exp) % 10];
    }
    for (int i = 1; i < count.size(); ++i) {
        count[i] +=  count[i - 1];
    }
    for (int i = inArr.size() - 1; i >= 0; --i) {
        outArr[--count[(inArr[i].key / exp) % 10]] = inArr[i];
    }
    for (int i = 0; i < outArr.size(); ++i) {
        inArr[i] = outArr[i];
    };
}

std::vector<Item> RadixSort(std::vector<Item>& inArr) {
    unsigned long int maxKey = GetMaxKey(inArr);
    for (int exp = 1; maxKey / exp > 0; exp *= 10)
        CountSort(inArr, exp);
    return inArr;
}

int main() {
    std::vector<Item> in_arr;
    Item in_item;
    while (std::cin >> in_item.key >> in_item.value) {
        in_arr.push_back(std::move(in_item));
    }
    std::vector<Item> outArr = RadixSort(in_arr);
    for (int i = 0; i < outArr.size(); i++) {
        std::cout << outArr[i].key << '\t' << outArr[i].value << '\n';
    }
    return 0;
}