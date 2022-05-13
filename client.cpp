#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>

#define NAME_FIFO   "namedpipe"
#define MAX_LINE    1024
#define MAX_CHAR    253

int main()
{
    std::fstream fstream; /* Поток ввода-вывода */
    char data[MAX_LINE]; /* Буфер для отправки информации */
    char path[MAX_CHAR]; /* Массив для сохраннеия пути к файлу */
    int fd, n;
    
    fd = open(NAME_FIFO, O_WRONLY);

    printf("Введите путь к файлу >> ");
    std::cin.getline(path, MAX_CHAR);

    /* Открытие изображения на бинарное чтение */
    fstream.open(path, std::fstream::binary | std::fstream::in);

    if (!fstream.is_open()) 
    {
        printf("\nError : Open File Failed \n");
        close(fd);
		exit(1);
    }

    /* Чтение данные из файла и отправление их по именованному каналу */
    while (!fstream.eof()) 
    {
        fstream.read(data, MAX_LINE);

        if( (n = write(fd, data, MAX_LINE)) < 0){
            perror("\nCan\'t write ");
            close(fd);
            exit(1);
        }
    }

    close(fd);
    return 0;
}