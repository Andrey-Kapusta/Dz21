#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>



void process_text(FILE* input, FILE* output);
int read_and_process_file(char* input_filename, char* output_filename);


int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "RUS");

    char input_filename[] = "winter.txt";
    char output_filename[100];

    printf("Введите имя файла для записи результата: ");
    scanf("%s", output_filename);


    if (read_and_process_file(input_filename, output_filename) == 0) {
        printf("Преобразование завершено. Результат записан в файл %s\n", output_filename);
    }
    else {
        printf("Произошла ошибка при обработке файлов!\n");
        return 1;
    }

    return 0;
}





void process_text(FILE* input, FILE* output) {
    int ch, prev_ch = ' ';


    while ((ch = fgetc(input)) != EOF) {

        if (isalpha(ch) && !isalpha(prev_ch) && prev_ch != '\'' && prev_ch != '-') {
            fputc('1', output); // Заменяем первую букву на '1'
        }
        else {
            fputc(ch, output); // Копируем символ без изменений
        }
        prev_ch = ch; // Запоминаем текущий символ как предыдущий
    }
}







int read_and_process_file(char* input_filename, char* output_filename) {
    FILE* input_file, * output_file;

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", input_filename);
        return 1;
    }


    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", output_filename);
        fclose(input_file);
        return 1;
    }


    process_text(input_file, output_file);


    fclose(input_file);
    fclose(output_file);

    return 0;
}
