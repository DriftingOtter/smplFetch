#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#define ANSI_COLOR_BLACK "\e[0;30m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_WHITE "\033[37m"
#define ANSI_COLOR_RESET "\x1b[0m"

char *get_Usr();
char *get_Distro();
char *get_KernelName();
char *get_KernelXver();
char *get_CurrentTime();
long get_usedMEM();
long get_totalMEM();
int get_batteryPercentage();
void generate_ColorStrip();

int main(int argc, char *argv[]) { // Holds Current Time
  char *currentTime = get_CurrentTime();

  printf("⎧                          ⎫\n");
  printf("⎮        ⎮%s⎮        ⎮\n", currentTime);
  printf("⎩                          ⎭\n");

  // Realocating Memory To System
  free(currentTime);

  printf("\n");

  // Holding Current User Name
  char *usr = get_Usr();
  printf("User:   %s\n", usr);

  // Realocating Memory To System
  free(usr);

  // Holding System Distrobution Name
  char *distroName = get_Distro();
  printf("Distro: %s\n", distroName);

  // Realocating Memory To System
  free(distroName);

  // Holding Kernal Name && System Version
  char *kernelName = get_KernelName();
  char *kernalXver = get_KernelXver();

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

  // Checking for color strip flag
  if (argc > 1 && strcmp(argv[1], "-cs") == 0) {
    generate_ColorStrip();
  } else if (argc > 1) {
    perror(ANSI_COLOR_RED "Invalid command-line argument. Please use the '-cs' "
                          "flag to generate the color strip." ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  return 0;
}

char *get_KernelName() {
  struct utsname kernelInfo;
  errno = 0;

  // Retrieve system information into struct
  if (uname(&kernelInfo) != 0) {
    perror(ANSI_COLOR_RED
           "uname doesn't return 0, so there is an error\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Gets size of kernal's sys name to avoid buffer overflow
  size_t length = strlen(kernelInfo.sysname) + 1;
  char *sysname = malloc(length);

  // Allocate memory for the kernel name
  if (sysname == NULL) {
    perror(ANSI_COLOR_RED "Failed to allocate memory\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Copy the kernel name and ensure null terminator
  strncpy(sysname, kernelInfo.sysname, length);
  sysname[length - 1] = '\0';

  return sysname;
}

char *get_KernelXver() {
  struct utsname kernelInfo;
  errno = 0;

  // Retrieve system information into struct
  if (uname(&kernelInfo) != 0) {
    perror(ANSI_COLOR_RED
           "uname doesn't return 0, so there is an error\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Gets size of kernal's sys name to avoid buffer overflow
  size_t length = strlen(kernelInfo.machine) + 1;
  char *xVer = malloc(length);

  // Allocate memory for the kernel version
  if (xVer == NULL) {
    perror(ANSI_COLOR_RED "Failed to allocate memory\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Copy the kernel version and ensure null terminator
  strncpy(xVer, kernelInfo.machine, length);
  xVer[length - 1] = '\0';

  return xVer;
}

char *get_Usr() {
  // Get the length of the username
  size_t length = strlen(getlogin()) + 1;

  // Allocates memory based on size of username
  char *usr = malloc(length);

  // Checking for no memory allocation error
  if (usr == NULL) {
    perror(ANSI_COLOR_RED "Failed to allocate memory\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Copy username to var
  strncpy(usr, getlogin(), length);

  // Ensuring NULL terminator
  usr[length - 1] = '\0';

  return usr;
}

char *get_Distro() {
  // Making pointer for File
  FILE *file = fopen("/etc/os-release", "r");

  // Error checking for file locating action
  if (file == NULL) {
    perror(ANSI_COLOR_RED
           "Failed to open ditro (/etc/os-release) file.\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  /* Allocating 256x of char type size
  Adding char pointer instead of void */
  char *buffer = (char *)malloc(256 * sizeof(char));

  if (buffer == NULL) {
    perror(ANSI_COLOR_RED "Memory allocation failed.\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Read the first line of the file
  if (fgets(buffer, 256, file) == NULL) {
    perror(ANSI_COLOR_RED "Error reading to buffer.\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Removing 'NAME=' from string's contents
  size_t length = strlen(buffer);

  if (length >= 5) {
    memmove(buffer, buffer + 5, length - 4);
  } else {
    buffer[0] = '\0';
  }

  // Removing '\n' escape character from contents
  size_t len = strlen(buffer);

  if (len > 0 && buffer[len - 1] == '\n')
    buffer[len - 1] = '\0';

  fclose(file);

  return buffer;
}

long get_usedMEM() {
  struct sysinfo info;
  long usedMemory;

  if (sysinfo(&info) == 0) {
    usedMemory = (info.totalram - info.freeram) * info.mem_unit;
  } else {
    perror(ANSI_COLOR_RED "Error In Getting RAM data.\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Converting from bytes to MB
  double usedMemoryGB;
  usedMemoryGB = (double)usedMemory / (1024 * 1024 * 1024);

  return usedMemoryGB;
}

long get_totalMEM() {
  struct sysinfo info;
  long totalMemory;

  if (sysinfo(&info) == 0) {
    totalMemory = info.totalram * info.mem_unit;
  } else {
    perror(ANSI_COLOR_RED "Error In Getting RAM data.\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  // Converting from bytes to MB
  double totalMemoryGB;
  totalMemoryGB = (double)totalMemory / (1024 * 1024 * 1024);

  return totalMemoryGB;
}

int get_batteryPercentage() {
  char line[256];
  int capacity;

  FILE *file = fopen("/sys/class/power_supply/BAT0/capacity", "r");

  // Checking both locations for battery percentage info
  if (file == NULL) {
    file = fopen("/sys/class/power_supply/BAT1/capacity", "r");

    if (file == NULL) {
      perror(ANSI_COLOR_RED
             "Failed to open battery capacity file.\n" ANSI_COLOR_RESET);
      exit(EXIT_FAILURE);
    }
  }

  if (fgets(line, sizeof(line), file) != NULL) {
    // Remove trailing newline character
    line[strcspn(line, "\n")] = '\0';

    // Convert the string to an integer
    capacity = atoi(line);
  } else {
    perror(ANSI_COLOR_RED
           "Error in allocating battery percentage.\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  fclose(file);

  return capacity;
}

void generate_ColorStrip() {
  char *coloredBlock = "██";

  printf(ANSI_COLOR_BLACK   "\n%s" ANSI_COLOR_RESET, coloredBlock);
  printf(ANSI_COLOR_RED     "%s"   ANSI_COLOR_RESET, coloredBlock);
  printf(ANSI_COLOR_GREEN   "%s"   ANSI_COLOR_RESET, coloredBlock);
  printf(ANSI_COLOR_YELLOW  "%s"   ANSI_COLOR_RESET, coloredBlock);
  printf(ANSI_COLOR_BLUE    "%s"   ANSI_COLOR_RESET, coloredBlock);
  printf(ANSI_COLOR_MAGENTA "%s"   ANSI_COLOR_RESET, coloredBlock);
  printf(ANSI_COLOR_CYAN    "%s"   ANSI_COLOR_RESET, coloredBlock);
  printf(ANSI_COLOR_WHITE   "%s\n" ANSI_COLOR_RESET, coloredBlock);
}

char *get_CurrentTime() {
  time_t currentTime;
  struct tm *localTime;

  char *timeString =
      (char *)malloc(sizeof(char) * 9); // Increase buffer size to 9

  // Obtain current time
  currentTime = time(NULL);

  // Convert the current time to the local time
  localTime = localtime(&currentTime);

  // Determine AM or PM
  const char *meridian = (localTime->tm_hour >= 12) ? "PM" : "AM";

  // Convert to 12-hour format
  int hour12 = (localTime->tm_hour % 12 == 0) ? 12 : localTime->tm_hour % 12;

  // Format the local time as a string in 12-hour format without seconds
  sprintf(timeString, "%02d:%02d %s", hour12, localTime->tm_min, meridian);

  return timeString;
}
