
// Homework 4
// Testing Sorting Algorithms
// Chethram Ramoutar

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

using namespace std;

// Computes duration given a start time and a stop time in nano seconds.
// Keep it in.
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time,
                          chrono::high_resolution_clock::time_point end_time)
{
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector)
{
  // Use rand() to generate random integer
  vector<int> new_vect(size_of_vector);
  for (size_t i = 0; i < size_of_vector; i++)
  { // fills the vector with random values
    new_vect[i] = rand();
  }
  return new_vect; // returns vect
}

// Generates and returns sorted vector of size @size_of_vector.
// If @smaller_to_larger is true, returns vector sorted from small to large.
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger)
{
  // Add code
  vector<int> new_vect(size_of_vector);
  for (size_t i = 0; i < size_of_vector; i++)
  {
    new_vect[i] = rand(); // creates a new vector of rand ints
  }
  if (smaller_to_larger == true)
  { // if the bool is true, sort from smaller to larger
    for (size_t curr_value = 0; curr_value < size_of_vector; curr_value++)
    { // compare every value of the vector to the other values
      for (size_t other_values = 0; other_values < size_of_vector; other_values++)
      {
        if (new_vect[curr_value] < new_vect[other_values])
        { // if the current value is less than the other value, swap
          swap(new_vect[curr_value], new_vect[other_values]);
        }
        else
        {
          continue;
        }
      }
    }
  }
  else if (smaller_to_larger == false)
  { // if it's to be sorted from greater to less, the bool will be false
    for (size_t curr_value = 0; curr_value < size_of_vector; curr_value++)
    {
      for (size_t other_values = 0; other_values < size_of_vector; other_values++)
      {
        if (new_vect[curr_value] > new_vect[other_values])
        {
          swap(new_vect[curr_value], new_vect[other_values]); // if the current value is greater than the other value, swap
        }
        else
        {
          continue;
        }
      }
    }
  }
  return new_vect;
}

// Verifies that a vector is sorted given a comparator.
// I.e. it applies less_than() for consecutive pair of elements and returns true
// iff less_than() is true for all pairs.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than)
{
  bool consistent = true; // defaulted to true
  for (size_t curr_value = 1; curr_value < input.size(); curr_value++)
  {
    for (size_t prev_value = curr_value - 1; prev_value < curr_value; prev_value++)
    {
      if (less_than(input[prev_value], input[curr_value]) || input[prev_value] == input[curr_value])
      { // if the vector's value and the value after it is compared to be true, continue
        continue;
      }
      else
      { // once found false, the bool value changes
        consistent = false;
      }
    }
  }
  return consistent; // return the bool value
}

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char **argv)
{
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small")
  {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0)
  {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater")
  {
    cout << "Invalid comparison type" << endl;
    return;
  }

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  vector<int> input_vector;
  if (input_type == "random")
  {
    // Generate random vector @input_vector.
    input_vector = GenerateRandomVector(input_size);
  }
  else
  {
    // Generate sorted vector @input_vector.
    if (input_type == "sorted_large_to_small")
    {
      input_vector = GenerateSortedVector(input_size, false);    }
    else if (input_type == "sorted_small_to_large")
    {
      input_vector = GenerateSortedVector(input_size, true);
    }
  }

  // Call HeapSort / MergeSort / QuickSort  using appropriate input.
  // ...
  // if comparison type is "less" then call
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for HeapSort & QuickSort
  if (comparison_type == "less")
  {
    cout << "HeapSort" << "\n" << endl;
    const auto begin_H_time = chrono::high_resolution_clock::now();
    HeapSort(input_vector, less<int>{});
    const auto end_H_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_H_time, end_H_time) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n" << endl;

    cout << "MergeSort" << "\n" << endl;
    const auto begin_M_time = chrono::high_resolution_clock::now();
    MergeSort(input_vector, less<int>{});
    const auto end_M_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_M_time, end_M_time) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n" << endl;
    
    cout << "QuickSort" << "\n" << endl;
    const auto begin_Q_time = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    const auto end_Q_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_Q_time, end_Q_time) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n" << endl;

    cout << "Testing Quicksort Pivot Implementations" << "\n" << endl;

    cout << "Median of Three" << "\n" << endl;
    const auto begin_Med_time = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    const auto end_Med_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_Med_time, end_Med_time) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n" << endl;
  }
  else
  {
    cout << "HeapSort" << "\n" << endl;
    const auto begin_H_time = chrono::high_resolution_clock::now();
    HeapSort(input_vector, greater<int>{});
    const auto end_H_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_H_time, end_H_time) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n" << endl;

    cout << "MergeSort" << "\n" << endl;
    const auto begin_M_time = chrono::high_resolution_clock::now();
    MergeSort(input_vector, greater<int>{});
    const auto end_M_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_M_time, end_M_time) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n" << endl;
    
    cout << "QuickSort" << "\n" << endl;
    const auto begin_Q_time = chrono::high_resolution_clock::now();
    QuickSort(input_vector, greater<int>{});
    const auto end_Q_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_Q_time, end_Q_time) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n" << endl;

    cout << "Testing Quicksort Pivot Implementations" << "\n" << endl;

    cout << "Median of Three" << "\n" << endl;
    const auto begin_Med_time = chrono::high_resolution_clock::now();
    QuickSort(input_vector, greater<int>{});
    const auto end_Med_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_Med_time, end_Med_time) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n" << endl;
  }
  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for QuickSort2 & QuickSort3
}

int main(int argc, char **argv)
{
  // DO NOT CHANGE or ADD ANY CODE in this function.
  if (argc != 4)
  {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }

  testSortingWrapper(argc, argv);

  return 0;
}
