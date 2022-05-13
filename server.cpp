#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <fstream>

#define NAME_FIFO   "namedpipe"
#define MAX_LINE    1024
#define MAX_CHAR    256

int main()
{
    std::fstream fstream; /* Поток ввода-вывода */
    char data[MAX_LINE]; /* Буфер для приёма информации */
    int fd, n;
    
    mknod(NAME_FIFO, S_IFIFO|0700, 0);

    fd = open(NAME_FIFO, O_RDONLY);

    /* Открытие файла на бинарную запись */
    fstream.open("Image.png", std::fstream::binary | std::fstream::out);

    if (!fstream.is_open()) 
    {
        printf("\nError : Open File Failed \n");
        close(fd);
        exit(1);
    }

    /* Чтение с именованного канала и запись полученых данных в файл */
    while((n = read(fd, data, MAX_LINE)) > 0)
    {
        fstream.write(data, n);
    }

    close(fd);
    remove(NAME_FIFO);

    return 0;
}