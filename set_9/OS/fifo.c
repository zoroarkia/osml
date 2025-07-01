#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char *fifopath = "type/myfifo";
    char writemsg[80] = "hello";
    char readmsg[80];

    mkfifo(fifopath, 0666);

    fd = open(fifopath, O_WRONLY);
    write(fd, writemsg, strlen(writemsg) + 1);

    close(fd);

    fd = open(fifopath, O_RDONLY);
    read(fd, readmsg, sizeof(readmsg));
    printf("Received msg: %s\n", writemsg);
    close(fd);

    return 0;
}
