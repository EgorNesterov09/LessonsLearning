#include <iostream>

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int* ptr = &arr[0];

    // Используем арифметику указателей для доступа к четвертому элементу
    int fourthElement = *(ptr + 3);

    std::cout << "4-й элемент массива: " << fourthElement << std::endl;

    return 0;
}
