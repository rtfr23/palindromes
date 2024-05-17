#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include <ctype.h>
#include <stdbool.h>
#define _CRT_NON_CONFORMING_WCSTOK
int isPalindrome(const wchar_t *word)
{
    if (word == NULL)
    {
        return false;
    }
    if (wcslen(word) == 1)
    {
        return false;
    }
    int len = wcslen(word);
    int i = 0;
    int j = len - 1;
    while (i < j)
    {
        wchar_t ch1 = word[i];
        wchar_t ch2 = word[j];
        if (ch1 != ch2)
        {
            return false;
        }
        i++;
        j--;
    }
    wprintf(L"%ls\n", word);
    return true;
}
void printWordPalindromes(wchar_t *buffer, int numbersword)
{
    wchar_t znak[] = L" ";
    wchar_t *word = wcstok(buffer, znak);
    int count = 0;

    while (word != NULL && count < numbersword)
    {
        isPalindrome(word);
        word = wcstok(NULL, znak);
        count++;
    }
}
void printSentsPalindromes(wchar_t *buffer, int numberssents)
{
    wchar_t *sents = NULL;
    wint_t c;
    int j = 0;
    for (int i = 0; i < numberssents; i++)
    {

        int k = 0;
        sents = malloc((wcslen(buffer) + 1) * sizeof(wchar_t));
        if (sents == NULL)
        {
            perror("Memory allocation error");
        }
        while ((c = buffer[j]) != L'.')
        {

            if (iswalpha(c))
            {
                sents[k] = c;
                k++;
            }
            j++;
        }
        sents[k] = L'\0';
        isPalindrome(sents);
        if (buffer[j] == L'.')
        {
            j++;
        }
        free(sents);
    }
}
int main(int argc, char *argv[])
{
    int numbersword = 0;
    int numberssents = 0;
    long size;
    wchar_t *buffer;

    // Проверяем, что был передан хотя бы один аргумент
    if (argc < 2)
    {
        printf("No input file specified\n");
        return 1;
    }

    // Открытие файла
    FILE *file = fopen(argv[1], "r");

    // Проверка файла на правильность открытия
    if (file == NULL)
    {
        printf("Not successful to open a file: %s\n", argv[1]);
        return 1;
    }

    // Получение размера файла и создание динамического массива buffer
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    buffer = malloc((size + 1) * sizeof(wchar_t));

    // Проверка buffer на правильность выделения памяти
    if (buffer == NULL)
    {
        perror("Memory allocation error");
        return 1;
    }

    // Запись элементов из файла в buffer с предварительной обработкой текста
    int i = 0;
    wint_t c;
    while ((c = fgetwc(file)) != WEOF)
    {
        if (iswalpha(c))
        {
            if (iswlower(c))
            {
                buffer[i] = c;
                i++;
            }
            else
            {
                c = _tolower(c);
                buffer[i] = c;
                i++;
            }
        }
        else if (c == L' ')
        {
            numbersword++;
            buffer[i] = c;
            i++;
        }
        else if (c == L'.')
        {
            numberssents++;
            buffer[i] = c;
            i++;
        }
    }
    numbersword++;
    buffer[i] = L'\0';
    printWordPalindromes(buffer, numbersword);
    printSentsPalindromes(buffer, numberssents);
    free(buffer);
    fclose(file);
    return 0;
}
