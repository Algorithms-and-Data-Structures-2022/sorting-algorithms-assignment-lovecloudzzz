#include "assignment/heap_sort.hpp"
#include <iostream>

#include <utility>  // swap
#include <cassert>  // assert

namespace assignment {

  void HeapSort::Sort(std::vector<int>& arr) const {
    // строим двоичную кучу ... BuildMaxHeap ...
    BuildMaxHeap(arr);

    // обходим элементы кучи с конца до корня (не включительно)
    for (int index = static_cast<int>(arr.size()) - 1; index > 0; index--) {
      // обмениваем местами корень (максимальный элемент) и последний элемент кучи ... std::swap ...
      std::swap( arr[0], arr[index]);

      // спускаем новый корневой узел вниз ... Heapify ...
      Heapify(arr, index, 0);
    }
  }

  void HeapSort::BuildMaxHeap(std::vector<int>& arr) {

    // Комментарии:
    // - построение начинается с последнего не листового узла (листовые узлы спускать не нужно - лишняя операция)
    // - индекс последнего не листового узла = parent (size - 1) = ((size - 1) - 1) / 2 = size / 2 - 1
    // - индекс идет до корня (включительно)

    const int size = static_cast<int>(arr.size());

    for (int i = size / 2 - 1; i >= 0; i--) {
      Heapify(arr, size, i);
    }
  }

  void HeapSort::Heapify(std::vector<int>& arr, int heap_size, int index) {
    assert(heap_size >= 0 && heap_size <= arr.size() && index >= 0 && index < heap_size);

    int largest = index;
    int temp = index;
    bool done = false;
    while (!done) {
      // вычисляем индексы потомков для текущего элемента
      int left_child = LeftChild(temp);
      int right_child = RightChild(temp);
      // поиск наибольшего элемента среди текущего элемента и его потомков ...
      if (left_child < heap_size and arr[largest] < arr[left_child]) {
        largest = left_child;
      }
      if (right_child < heap_size and arr[largest] < arr[right_child]) {
        largest = right_child;
      }
      // если текущий элемент больше своих потомков, то он находится на правильном месте (свойство макс. кучи)
      if (largest != temp) {
        std::swap(arr[largest], arr[temp]);
        temp = largest;
      }
      else {
        done = true;
      }
    }
  }

  int HeapSort::Parent(int index) {
    assert(index >= 0);
    return index / 2 - 1;
  }

  int HeapSort::LeftChild(int index) {
    assert(index >= 0);
    return 2 * index + 1;
  }

  int HeapSort::RightChild(int index) {
    assert(index >= 0);
    return 2 * index + 2;
  }

}  // namespace assignment
