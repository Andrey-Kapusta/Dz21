#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "func.h"
#define MAX_SIZE 100


int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "RUS");

    cornice_t cornices[MAX_SIZE];
    int size = 0;
    int choice;

    printf("\n=== БАЗА ДАННЫХ КАРНИЗОВ ===\n");

    do {
        printf("\n=== МЕНЮ ПРОГРАММЫ ===\n");
        printf("1. Загрузить из файла\n");
        printf("2. Сохранить в файл\n");
        printf("3. Заполнить массив случайными значениями\n");
        printf("4. Вывести все записи\n");
        printf("5. Изменить запись\n");
        printf("6. Найти запись\n");
        printf("7. Отсортировать массив\n");
        printf("8. Выход\n");
        printf("\nВыберите действие: ");

        scanf("%d", &choice);
        switch (choice) {


        case 1: {
            char filename[50];
            printf("Введите имя файла с расширением для загрузки содержимого:  ");
            scanf("%s", filename);

            size = input_file(filename, cornices, MAX_SIZE);
            break;
        }




        case 2: {
            char new_filename[50];
            printf("Введите имя файла с расширением для сохранения:  ");
            scanf("%s", new_filename);


            if (size > 0) {
                output_file(new_filename, cornices, size);
            }
            else {
                printf("Массив пуст! Нет данных для сохранения!\n");
            }
            break;
        }



        case 3:
            printf("Введите количество записей (макс. %d): ", MAX_SIZE);
            scanf("%d", &size);
            if (size > 0 && size <= MAX_SIZE) {
                fill_array_random(cornices, size);
            }
            else {
                printf("Неверное количество записей.\n");
            }
            break;



        case 4:
            print_array(cornices, size);
            break;



        case 5:
            edit_record(cornices, size);
            break;



        case 6:
            search_record(cornices, size);
            break;



        case 7:
            if (size == 0) {
                printf("Массив пуст!\n");
                break;
            }
            printf("\nВыберите поле для сортировки:\n");
            printf("1. Длина -> Ширина -> Высота\n");
            printf("2. Площадь (Длина * Ширина)\n");
            printf("3. Материал\n");
            printf("Ваш выбор: ");

            int key_sort;
            scanf("%d", &key_sort);
            sort_array(cornices, size, key_sort);
            break;





        case 8:
            printf("Выход из программы.\n");
            break;



        default:
            printf("Неверный выбор! Попробуйте снова\n");
        }
    } while (choice != 8);

    return 0;

}


