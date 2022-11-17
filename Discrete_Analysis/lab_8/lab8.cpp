#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

struct SegmentBoundaries
{
    int left, right;
};

int n, m;
std::vector<SegmentBoundaries> in_segments;
std::vector<int> ans_indx;

void LongestSegmentContainingLeft(int left){
    int max_r = -1, max_i = -1;
    if(ans_indx.size() > 0)
        max_r = in_segments[ans_indx.back()].right;
    for(int i = 0; i < n; ++i){
        if(in_segments[i].right > max_r && in_segments[i].left <= left){
            max_r = in_segments[i].right;
            max_i = i;
        }
    }
    if(max_i < 0)
        return;
    ans_indx.push_back(max_i);
    if(max_r < m)
        LongestSegmentContainingLeft(max_r);
}

int main(){
    std::cin >> n;
    in_segments.resize(n);
    for(int i = 0; i < n; ++i)
        std::cin >> in_segments[i].left >> in_segments[i].right;
    std::cin >> m;  
    auto start = std::chrono::steady_clock::now();
    LongestSegmentContainingLeft(0);
    auto finish = std::chrono::steady_clock::now();
    if(in_segments[ans_indx.back()].right >= m) {
        std::sort(ans_indx.begin(), ans_indx.end());
        std::cout << ans_indx.size() << std::endl;
        for(auto it = ans_indx.begin(); it != ans_indx.end(); ++it)
            std::cout << in_segments[*it].left << ' ' << in_segments[*it].right << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }
    unsigned time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    std::cout << "!!! " << time << " !!!\n";
    return 0;
}