#include <stdio.h>
#include <stdlib.h>


void print_mas(int *list)
{
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", list[i]);
    }
}



int *count_sort(int *mas, int amount) 
{
    int max = mas[0], min = mas[0];
    int size_count;
    int *count_mas;
    int *sorted_mas;

    for (int i = 1; i < amount; i++) {
        if (mas[i] < min)
            min = mas[i];
        else if (mas[i] > max)
            max = mas[i];
    }

    size_count = max - min + 1;

    count_mas = (int *) malloc(sizeof(int) * size_count);
    sorted_mas = (int *) malloc(sizeof(int) * amount);

    for (int i = 0; i < size_count; i++)
        count_mas[i] = 0;
    for (int i = 0; i < amount; i++)
        sorted_mas[i] = 0;

    for (int i = 0; i < amount; ++i)
        count_mas[mas[i] - min] += 1;

    int j = 0;
    for (int i = 0; i < size_count; i++) {
        while (count_mas[i] > 0) {
            sorted_mas[j] = min;
            j++;
            count_mas[i]--;
        }
        min++;
    }

    return sorted_mas;
}
// ----------------------------------------------------------

void merge(int mas[], int left, int mid, int right) { 
    int i, j; 
    int len_left = mid - left + 1; 
    int len_right = right - mid; 

    int left_arr[len_left], right_arr[len_right]; 
  
    for (i = 0; i < len_left; i++) 
        left_arr[i] = mas[left + i]; 
    for (j = 0; j < len_right; j++) 
        right_arr[j] = mas[mid + 1 + j]; 
  
    i = j = 0; 
    while (i < len_left && j < len_right) { 
        if (left_arr[i] <= right_arr[j])
            mas[left++] = left_arr[i++]; 
        else
            mas[left++] = right_arr[j++];
    } 
  
    while (i < len_left)
        mas[left++] = left_arr[i++]; 

    while (j < len_right)
        mas[left++] = right_arr[j++]; 
} 

void merge_sort(int mas[], int left, int right) { 
    if (left < right) { 
        int mid = left + (right - left) / 2; 
        merge_sort(mas, left, mid); 
        merge_sort(mas, mid + 1, right); 
        merge(mas, left, mid, right); 
    } 
} 
// ---------------------------------------------------------

void radixSort(int *arr, int start, int end) 
{
    int radix_base = 10; // Основание системы счисления
    int max_num = arr[0]; // Максимальное число в массиве
    for (int i = start; i < end; ++i) // Поиск максимального числа в массиве
        if (max_num < arr[i]) max_num = arr[i];
    int radx = 0;
    while (max_num != 0) 
    { 
        radx++;
        max_num /= radix_base;
    }
    int *base_arr = malloc(sizeof(int) * radix_base); // Массив для хранения колва чисел в каждом отсеке массива по разрядам
    for (int i = 0; i < radix_base; ++i) base_arr[i] = 0; // Заполняем его нулями
    int **digits_arr = malloc(sizeof(int*) * radix_base); // Массив массивов с числами, по разрядам
    for (int i = 0; i < radix_base; ++i)
        digits_arr[i] = malloc(sizeof(int) * (end - start + 1));

    for (int i = 0; i < radx; ++i) 
    {
        for (int j = start; j < end; ++j) // Разбиваем исходный массив по разрядному числу во вспомогательный массив, попутно считая кол-во чисел в каждой ячейке
        { 
            int digit = (arr[j] / pow_(radix_base, i)) % radix_base;
            digits_arr[digit][base_arr[digit]++] = arr[j];
        }
        int count = 0;
        for (int j = 0; j < radix_base; ++j) // Собираем исходный массив обратно
        { 
            for (int k = 0; k < base_arr[j]; ++k) {
                arr[count++] = digits_arr[j][k];
            }
        }
        for (int j = 0; j < radix_base; ++j) base_arr[j] = 0;
    }

    for (int i = 0; i < radix_base; ++i)
        free(digits_arr[i]);
    free(digits_arr);
    free(base_arr);
}
   
// ---------------------------------------------------------


void qsort (int *mas, int a, int b) {
    int left = a, right = b;
    int pivot = mas[(left + right)/2];
	do {
		while (mas[left] < pivot) {
			left++;
		}
		while (mas[right] > pivot) {
			right--;
		}
		if (left <= right) {
			if (mas[left] > mas[right]) {
				int tmp = mas[left];
				mas[left] = mas[right];
				mas[right] = tmp;
			}
			left++;
			if (right > 0) {
				right--;
			}
		}
	} while (left <= right);

	if (left < b) {
		qsort(mas, left, b);
	}
	if (right > a) {
		qsort(mas, a, right);
	}
}

// ---------------------------------------------------------
int main(void)
{
    int mas[] =  {0, 3, 2, 1, 4};
    merge_sort(mas, 0, 5-1);
    print_mas(mas);
    // print_mas(count_sort(mas, 5));

    return 0;
}