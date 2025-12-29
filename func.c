#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"


int getRandomNumber(int min, int max) {

    return (rand() % (max - min + 1) + min);
}





void getRandomString(char* str, int max_len) {

    const char* materials[] = {
        "Дерево",
        "Алюминий",
        "Пластик",
        "Композит",
        "Пенопласт",
        "Сталь",
        "Металл"
    };

    int count = sizeof(materials) / sizeof(materials[0]);
    strcpy(str, materials[rand() % count]);

}


void fill_array_random(cornice_t* cornices, int size) {

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        cornices[i].length = getRandomNumber(1, 12) * 100;
        cornices[i].ceilingWidth = getRandomNumber(1, 7) * 10;
        cornices[i].wallHeight = getRandomNumber(2, 9) * 10;
        getRandomString(cornices[i].material, 20);
    }
    printf("Массив заполнен случайными значениями\n");

}




void print_cornice(cornice_t cornice) {

    printf("| %4d мм | %4d мм | %4d мм | %19s |\n", cornice.length, cornice.ceilingWidth, cornice.wallHeight, cornice.material);

}



void print_array(cornice_t* cornices, int size) {

    if (size == 0) {
        printf("Массив пуст.\n");
        return;
    }

    printf("\n============================================================\n");
    printf("|  №   | Длина   | Ширина  | Высота  | Материал            |\n");
    printf("============================================================\n");
    for (int i = 0; i < size; i++) {
        printf("| №%3d ", (i + 1));
        print_cornice(cornices[i]);
    }
    printf("============================================================\n");
    printf("Всего записей: %d\n", size);

}




void edit_record(cornice_t* cornices, int size) {

    if (size == 0) {
        printf("Массив пуст!\n");
        return;
    }

    int index;
    printf("Введите номер записи для изменения (1-%d): ", size);
    scanf("%d", &index);

    if (index < 1 || index > size) {
        printf("Неверный номер записи!\n");
        return;
    }

    index--;

    printf("\nТекущая запись:\n");
    printf("=======================================================\n");
    printf("| №%3d ", (index + 1));
    print_cornice(cornices[index]);
    printf("=======================================================\n");

    printf("\nВведите новые значения:\n");
    printf("Длина (мм): ");
    scanf("%d", &cornices[index].length);
    printf("Ширина по потолку (мм): ");
    scanf("%d", &cornices[index].ceilingWidth);
    printf("Высота по стене (мм): ");
    scanf("%d", &cornices[index].wallHeight);
    printf("Материал: ");
    scanf("%s", cornices[index].material);

    printf("Запись успешно изменена.\n");

}






cornice_t* search_length(cornice_t* cornices, int size, int length) {

    for (int i = 0; i < size; i++) {
        if (cornices[i].length == length) {
            return (cornices + i);
        }
    }
    return NULL;

}

cornice_t* search_wallHeight(cornice_t* cornices, int size, int wallHeight) {

    for (int i = 0; i < size; i++) {
        if (cornices[i].wallHeight == wallHeight) {
            return (cornices + i);
        }
    }
    return NULL;

}

cornice_t* search_ceilingWidth(cornice_t* cornices, int size, int ceilingWidth) {

    for (int i = 0; i < size; i++) {
        if (cornices[i].ceilingWidth == ceilingWidth) {
            return (cornices + i);
        }
    }
    return NULL;

}



cornice_t* search_material(cornice_t* cornices, int size, char* material) {

    for (int i = 0; i < size; i++) {
        if (strcmp(cornices[i].material, material) == 0) {
            return (cornices + i);
        }
    }
    return NULL;

}












void search_record(cornice_t* cornices, int size) {

    if (size == 0) {
        printf("Массив пуст. Нет записей для поиска.\n");
        return;
    }

    int choice;
    printf("\nВыберите пункт для поиска:\n");
    printf("1. Длина детали\n");
    printf("2. Ширина по потолку\n");
    printf("3. Высота по стене\n");
    printf("4. Материал\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    cornice_t* found = NULL;

    switch (choice) {

    case 1: {
        int length;
        printf("Введите длину для поиска (мм): ");
        scanf("%d", &length);
        found = search_length(cornices, size, length);
        break;
    }
    case 2: {
        int wallHeight;
        printf("Введите ширину для поиска (мм): ");
        scanf("%d", &wallHeight);
        found = search_wallHeight(cornices, size, wallHeight);
        break;
    }
    case 3: {
        int ceilingWidth;
        printf("Введите высоту для поиска (мм): ");
        scanf("%d", &ceilingWidth);
        found = search_ceilingWidth(cornices, size, ceilingWidth);
        break;
    }
    case 4: {
        char material[20];
        printf("Введите материал для поиска: ");
        scanf("%s", material);
        found = search_material(cornices, size, material);
        break;
    }
    default:
        printf("Неверный выбор.\n");
        return;
    }

    if (found != NULL) {
        printf("\nНайдена запись:\n");
        printf("===============================================\n");
        printf("| Длина | Ширина | Высота | Материал        |\n");
        printf("===============================================\n");
        print_cornice(*found);
        printf("===============================================\n");
    }
    else {
        printf("Запись не найдена.\n");
    }

}
















int compare(const void* a, const void* b) {

    const cornice_t* corniceA = (const cornice_t*)a;
    const cornice_t* corniceB = (const cornice_t*)b;

    if (corniceA->length < corniceB->length) {
        return -1;
    }
    else if (corniceA->length > corniceB->length) {
        return 1;
    }
    else if (corniceA->length == corniceB->length) {
        if (corniceA->ceilingWidth < corniceB->ceilingWidth) {
            return -1;
        }
        else if (corniceA->ceilingWidth > corniceB->ceilingWidth) {
            return 1;
        }
        else if (corniceA->ceilingWidth == corniceB->ceilingWidth) {
            if (corniceA->wallHeight < corniceB->wallHeight) {
                return -1;
            }
            else if (corniceA->wallHeight > corniceB->wallHeight) {
                return 1;
            }
        }
    }
    return 0;
}





int compare_area(const void* a, const void* b) {

    const cornice_t* corniceA = (const cornice_t*)a;
    const cornice_t* corniceB = (const cornice_t*)b;

    int areaA = corniceA->length * corniceA->ceilingWidth;
    int areaB = corniceB->length * corniceB->ceilingWidth;

    if (areaA < areaB) return -1;
    else if (areaA > areaB) return 1;
    return 0;

}




int compare_material(const void* a, const void* b) {

    const cornice_t* corniceA = (const cornice_t*)a;
    const cornice_t* corniceB = (const cornice_t*)b;
    return strcmp(corniceA->material, corniceB->material);

}






void sort_array(cornice_t* cornices, int size, int key_sort) {

    switch (key_sort) {
    case 1:
        qsort(cornices, size, sizeof(cornice_t), compare);
        printf("Сортировка по Длине -> Ширине -> Высоте выполнена\n");
        break;
    case 2:
        qsort(cornices, size, sizeof(cornice_t), compare_area);
        printf("Сортировка по Площади выполнена\n");
        break;
    case 3:
        qsort(cornices, size, sizeof(cornice_t), compare_material);
        printf("Сортировка по Материалу выполнена.\n");
        break;
    default:
        printf("Неверный выбор поля для сортировки!\n");
    }

}







int output_file(char* filename, cornice_t* arr, int n) {

    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла для записи!\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d %d %d %s\n", arr[i].length, arr[i].ceilingWidth, arr[i].wallHeight, arr[i].material);
    }

    fclose(file);
    printf("Данные успешно записаны в файл '%s' (%d записей).\n", filename, n);
    return 1;

}

int input_file(char* filename, cornice_t* arr, int max_size) {

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла для чтения!\n");
        return 0;
    }

    int count = 0;
    while (count < max_size && fscanf(file, "%d %d %d %19s", &arr[count].length, &arr[count].ceilingWidth, &arr[count].wallHeight, arr[count].material) == 4) {
        count++;
    }

    fclose(file);
    printf("Загружено %d записей из файла '%s'.\n", count, filename);
    return count;

}









