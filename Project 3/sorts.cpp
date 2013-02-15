#include <vector>
#include <string>
#include <iostream>
using namespace std;


// Swaps the two vector elements
void swap(vector<string>& list, int i1, int i2) {
	string temp = list[i1];
	list[i1] = list[i2];
	list[i2] = temp;
}

// Quick sorting algorithm for strings
void quicksort(vector<string>& list, int begin, int end) {
	string pivot = list[end];
	int x = begin; // keep track of new pivot index
	for(int i = begin; i < end; i++) {
		if(pivot.compare(list[i]) > 0) { // Check if current value is less than pivot
			swap(list, i, x);
			x++;
		}
	}
	swap(list, end, x); // swap pivot with new pivot index
	if(x - begin > 1) { // Continue recursivly on beginning of list
		quicksort(list, begin, x - 1);
	}
	if(end - x > 1) { // Continue recursivly on end of list
		quicksort(list, x + 1, end);
	}
}

// Merges two sorted lists of strings into a single sorted list of strings
vector<string> merge(vector<string> left, vector<string> right) {
    vector<string> result;
    unsigned int i = 0, j = 0;
    while(i < left.size() && j < right.size()) { // While both lists have values
        if(left[i].compare(right[j]) < 0) { // Compare the current values of each list
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    
    while(i < left.size()) { // Push in remaining left values
        result.push_back(left[i]);
        i++;
    }
    while(j < right.size()) { // Push in remaining right values
        result.push_back(right[j]);
        j++;
    }
    
    return result;
}

// Merge sorting algorithm for strings
void mergesort(vector<string>& list) {
    if (list.size() <= 1) { // 1 element list is already sorted
        return;
    }
    
    // Split the list in two halves
    int middle = int(list.size()/2);
    vector<string> left(&list[0], &list[middle]);
    vector<string> right(&list[middle], &list[list.size()]);
    // recursively mergesort both halves
    mergesort(left);
    mergesort(right);
    // Combine the two sorted lists
    list = merge(left, right);
}