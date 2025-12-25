#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Структура для хранения информации об автомобиле
typedef struct {
    char brand[50];        // Марка автомобиля
    char manufacturer[50]; // Производитель
    char type[50];         // Тип
    int year_of_manufacture; // Год выпуска
    int registration_year;   // Год регистрации
} Car;




int writefile(char* fname, Car* cars, int size);
int input_car(Car* car);




int main() {
    system("chcp 1251");
    setlocale(LC_CTYPE, "RUS");

    char filename[100];
    int choice, size = 0;
    Car cars[100]; // Максимум 100 автомобилей

    printf("=== ПРОГРАММА ДЛЯ РАБОТЫ С АВТОМОБИЛЯМИ ===\n");

    do {
        printf("\nМеню:\n");
        printf("1. Ввод новых автомобилей\n");
        printf("2. Сохранить в файл\n");
        printf("3. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {


        case 1: // Ввод новых автомобилей
            if (size >= 100) {
                printf("Достигнут максимальный размер базы данных!\n");
                break;
            }

            printf("Сколько автомобилей вы хотите добавить? ");
            int count;
            scanf("%d", &count);

            if (size + count > 100) {
                printf("Превышен максимальный размер! Можно добавить только %d автомобилей.\n", 100 - size);
                count = 100 - size;
            }

            for (int i = 0; i < count; i++) {
                printf("\nАвтомобиль %d из %d:\n", i + 1, count);
                if (input_car(&cars[size + i])!=1) printf("Ошибка записи");
            }
            size += count;
            printf("\nВведено %d автомобилей. Всего в базе: %d\nДля сохранения базы в файл выберете 2 пункт\n\n\n", count, size);
            break;






        case 2: // Сохранить в файл
            if (size == 0) {
                printf("Нет данных для сохранения!\n");
                break;
            }

            printf("Введите имя файла для сохранения (поставьте на конце .txt): ");
            scanf("%s", filename);

            if (writefile(filename, cars, size)) {
                printf("Данные успешно сохранены в файл '%s'\n", filename);
            }
            else {
                printf("Ошибка при сохранении данных!\n");
            }
            break;



        case 3: 
            printf("Выход из программы.\n");
            break;




        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            break;
        }
    } while (choice != 3);

    return 0;
}







// Функция записи массива структур в файл
int writefile(char* fname, Car* cars, int size) {
    FILE* out;


    if ((out = fopen(fname, "wt")) == NULL) {
        printf("Ошибка открытия файла для записи\n");
        return 0;
    }



    for (int i = 0; i < size; i++) {
        fprintf(out, "Бренд:%s Производитель:%s Тип:%s Год выпуска:%d Год регистрации:%d\n",
            cars[i].brand,
            cars[i].manufacturer,
            cars[i].type,
            cars[i].year_of_manufacture,
            cars[i].registration_year);
    }

    fclose(out);
    return 1;
}












// Функция ввода одной записи с клавиатуры
int input_car(Car* car) {
    printf("\n=== Ввод данных об автомобиле ===\n");

    printf("Марка автомобиля (без пробелов): ");
    scanf("%s", car->brand);

    printf("Производитель (без пробелов): ");
    scanf("%s", car->manufacturer);

    printf("Тип (без пробелов): ");
    scanf("%s", car->type);

    printf("Год выпуска: ");
    scanf("%d", &car->year_of_manufacture);

    printf("Год регистрации: ");
    scanf("%d", &car->registration_year);
    return 1;
}







