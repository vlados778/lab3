#include <iostream>

using namespace std;


void print_array(string name, int array[], int N)
{
    cout << name << ": ";
    for (int i = 0; i < N; i++)
        cout << array[i] << " ";
    cout << endl;
}


int main()
{
    srand(time(0));


    const int N = 10;


    int array_1[N];
    int array_2[N];
    int array_3[N];


    for (int i = 0; i < N; i++)
    {

        array_1[i] = rand() % 10;
        array_2[i] = rand() % 10;
    }


    int* ptr_a1 = array_1;
    int* ptr_a2 = array_2;
    int* ptr_a3 = array_3;

    asm(
            "mov %[ptr_a1], %%rsi   \n\t" // Ссылка на первый массив
            "mov %[ptr_a2], %%rdi   \n\t" // Ссылка на второй массив
            "mov %[ptr_a3], %%rdx   \n\t" // Ссылка на третий массив
            "mov %[N], %%ecx       \n\t" // Размерность массива
            
        "main_loop:                 \n\t"
            "mov (%%rsi), %%eax    \n\t" // Берем значение из первого массива
            "mov (%%rdi), %%ebx    \n\t" // Берем значение из второго массива
            "cmp %%eax, %%ebx      \n\t" // Сравниваем эти значение
            "jg write               \n\t" // Если значение второго больше первого, то пропускаем действие 
            "mov %%ebx, %%eax      \n\t" // Иначе выбираем для записи значение из второго массива
        
        "write:                     \n\t" 
            "mov %%eax, (%%rdx)    \n\t" // Помещаем выбранное число в 3 массив
            "add $4, %%rsi          \n\t" // Переходим к след. елементу у всех массивов
            "add $4, %%rdi          \n\t" // (4 из-за того, что int = 4 байта)
            "add $4, %%rdx          \n\t"
            "loop main_loop         \n\t" // Повторяем действие N раз
            :

            :[ptr_a1]"m"(ptr_a1), [ptr_a2]"m"(ptr_a2), [ptr_a3]"m"(ptr_a3), [N]"m"(N)
            :"%rax", "%rbx", "%rcx", "%rdx", "%rsi", "%rdi"
       );


    print_array("Array 1", array_1, N);
    print_array("Array 2", array_2, N);
    

    for (int i = 0; i < 35; i++)
        cout << "-";
    cout << endl;


    print_array("Array 3", array_3, N);

    return 0;
}
