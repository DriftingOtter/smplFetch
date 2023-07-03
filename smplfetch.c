#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <errno.h>
#include <string.h>

char* get_KernelName();
char* get_KernelXver();


int main(int argc, char *argv[])
{
    // Holding Kernal Name && System Version
    char* kernelName = get_KernelName();
    char* kernalXver = get_KernelXver();

    printf("Kernal: %s | %s\n", kernelName, kernalXver);

    // Realocating Memory To System
    free(kernelName);
    free(kernalXver);

    
    return 0;
}

char* get_KernelName()
{
    struct utsname kernelInfo;
    errno = 0;

    // Retrieve system information into struct
    if (uname(&kernelInfo) != 0) {
        perror("uname doesn't return 0, so there is an error\n");
        exit(EXIT_FAILURE);
    }

    // Gets size of kernal's sys name to avoid buffer overflow
    size_t length = strlen(kernelInfo.sysname) + 1;
    char* sysname = malloc(length);

    // Allocate memory for the kernel name
    if (sysname == NULL) {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    // Copy the kernel name and ensure null terminator
    strncpy(sysname, kernelInfo.sysname, length);
    sysname[length - 1] = '\0';

    return sysname;
}

char* get_KernelXver()
{
    struct utsname kernelInfo;
    errno = 0;

    // Retrieve system information into struct
    if (uname(&kernelInfo) != 0) {
        perror("uname doesn't return 0, so there is an error\n");
        exit(EXIT_FAILURE);
    }

    // Gets size of kernal's sys name to avoid buffer overflow
    size_t length = strlen(kernelInfo.machine) + 1;
    char* xVer = malloc(length);

    // Allocate memory for the kernel version
    if (xVer == NULL) {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    // Copy the kernel version and ensure null terminator
    strncpy(xVer, kernelInfo.machine, length);
    xVer[length - 1] = '\0';

    return xVer;
}
