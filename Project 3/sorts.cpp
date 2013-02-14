#include <vector>
#include <string>
#include <iostream>
using namespace std;


void swap(vector<string>& list, int i1, int i2) {
	string temp = list[i1];
	list[i1] = list[i2];
	list[i2] = temp;
}

void quicksort(vector<string>& list, int begin, int end) {
	string pivot = list[end];
	int x = begin;
	for(int i = begin; i < end; i++) {
		if(pivot.compare(list[i]) > 0) {
			swap(list, i, x);
			x++;
		}
	}
	swap(list, end, x);
	if(x - begin > 1) {
		quicksort(list, begin, x - 1);
	}
	if(end - x > 1) {
		quicksort(list, x + 1, end);
	}
}

vector<string> merge(vector<string> left, vector<string> right) {
    vector<string> result;
    unsigned int i = 0, j = 0;
    while(i < left.size() && j < right.size()) {
        if(left[i].compare(right[j]) < 0) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    
    while(i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while(j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
    
    return result;
}


void mergesort(vector<string>& list) {
    if (list.size() <= 1) {
        return;
    }
    
    int middle = int(list.size()/2);
    vector<string> left(&list[0], &list[middle]);
    vector<string> right(&list[middle], &list[list.size()]);
    mergesort(left);
    mergesort(right);
    list = merge(left, right);
}