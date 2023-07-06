#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


char* get_Usr();
char* get_Distro();
char* get_KernelName();
char* get_KernelXver();
long get_usedMEM();
long get_totalMEM();
int get_batteryPercentage();


int main(int argc, char *argv[])
{
    // Holding Current User Name
    char* usr = get_Usr();
    printf("User:   %s\n", usr);

    // Realocating Memory To System
    free(usr);


    // Holding System Distrobution Name
    char* distroName = get_Distro();
    printf("Distro: %s\n", distroName);

    // Realocating Memory To System
    free(distroName);


    // Holding Kernal Name && System Version
    char* kernelName = get_KernelName();
    char* kernalXver = get_KernelXver();

    printf("Kernal: %s | %s\n", kernelName, kernalXver);

    // Realocating Memory To System
    free(kernelName);
    free(kernalXver);


    // Holding Current System Memory Useage
    long usedMEM = get_usedMEM();
    long totalMEM = get_totalMEM();

    printf("Memory: %ldGB/%ldGB\n", usedMEM, totalMEM);

    // Holding Current Battery Percentage
    int batteryPercentage = get_batteryPercentage();
    printf("Battery: %i%%\n", batteryPercentage);

    return 0;
}


char* get_KernelName()
{
    struct utsname kernelInfo;
    errno = 0;

    // Retrieve system information into struct
    if (uname(&kernelInfo) != 0) 
    {
        perror("uname doesn't return 0, so there is an error\n");
        exit(EXIT_FAILURE);
    }

    // Gets size of kernal's sys name to avoid buffer overflow
    size_t length = strlen(kernelInfo.sysname) + 1;
    char* sysname = malloc(length);

    // Allocate memory for the kernel name
    if (sysname == NULL) 
    {
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
    if (uname(&kernelInfo) != 0) 
    {
        perror("uname doesn't return 0, so there is an error\n");
        exit(EXIT_FAILURE);
    }

    // Gets size of kernal's sys name to avoid buffer overflow
    size_t length = strlen(kernelInfo.machine) + 1;
    char* xVer = malloc(length);

    // Allocate memory for the kernel version
    if (xVer == NULL) 
    {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    // Copy the kernel version and ensure null terminator
    strncpy(xVer, kernelInfo.machine, length);
    xVer[length - 1] = '\0';

    return xVer;
}


char* get_Usr()
{
    // Get the length of the username
    size_t length = strlen(getlogin()) + 1;

    // Allocates memory based on size of username
    char* usr = malloc(length);

    // Checking for no memory allocation error
    if (usr == NULL)
    {
        perror("Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    // Copy username to var
    strncpy(usr, getlogin(), length);

    // Ensuring NULL terminator
    usr[length - 1] = '\0';

    return usr;
}

char* get_Distro()
{
    // Making pointer for File
    FILE* file = fopen("/etc/os-release", "r");

    // Error checking for file locating action
    if (file == NULL)
    {
        perror("Failed to open file.\n");
        exit(EXIT_FAILURE);
    }

    /* Allocating 256x of char type size
    Adding char pointer instead of void */
    char* buffer = (char*) malloc(256 * sizeof(char));

    if (buffer == NULL)
    {
        perror("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read the first line of the file
    if (fgets(buffer, 256, file) == NULL)
    {
        perror("Error reading file.\n");
        exit(EXIT_FAILURE);
    }

    // Removing 'NAME=' from string's contents
    size_t length = strlen(buffer);
   
    if (length >= 5)
    {
        memmove(buffer, buffer + 5, length - 4);
    }
    else
    {
        buffer[0] = '\0';
    }

    // Removing '\n' escape character from contents
    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    fclose(file);

    return buffer;
}

long get_usedMEM()
{
    struct sysinfo info;
    long usedMemory;

    if (sysinfo(&info) == 0) {
        usedMemory = (info.totalram - info.freeram) * info.mem_unit;
    } else {
        perror("Error In Getting RAM data.\n");
        exit(EXIT_FAILURE);
    }

    // Converting from bytes to MB
    double usedMemoryGB;
    usedMemoryGB = (double) usedMemory / (1024 * 1024 * 1024);

    return usedMemoryGB;
}

long get_totalMEM()
{
    struct sysinfo info;
    long totalMemory;

    if (sysinfo(&info) == 0) {
        totalMemory = info.totalram * info.mem_unit;
    } else {
        perror("Error In Getting RAM data.\n");
        exit(EXIT_FAILURE);
    }

    // Converting from bytes to MB
    double totalMemoryGB;
    totalMemoryGB = (double) totalMemory / (1024 * 1024 * 1024);

    return totalMemoryGB;
}

int get_batteryPercentage()
{
    char path[256];
    char line[256];
    int capacity;

    FILE* file = fopen("/sys/class/power_supply/BAT0/capacity", "r");

    // Checking both locations for battery percentage info
    if (file == NULL) 
    {
        file = fopen("/sys/class/power_supply/BAT1/capacity", "r");

        if (file == NULL)
        {
            perror("Failed to open battery capacity file.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (fgets(line, sizeof(line), file) != NULL) 
    {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Convert the string to an integer
        capacity = atoi(line);
    }
    else
    {
        perror("Error in allocating battery percentage.\n");
        exit(EXIT_FAILURE);
    }

    fclose(file);

    return capacity;
}
