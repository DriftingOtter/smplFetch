#!/sbin/python

import sys
import platform
import psutil
import random
from colorama import init, Style
from termcolor import colored
init()

colors = ['black', 'red', 'green', 'yellow', 'blue', 'magenta', 'cyan', 'white']

def get_Distro():
    distro = platform.node()
    return distro

def get_OS():
    operatingSystem = platform.system()
    return operatingSystem

def get_Xver():
    xVer = platform.machine()
    return xVer

def get_SysMemoryTotal():
    totalMem = psutil.virtual_memory()
    totalMem = round(totalMem.total / (1024 ** 3))
    return totalMem

def get_SysMemoryUsed():
    usedMem = psutil.virtual_memory()
    usedMem = round(usedMem.used / (1024 ** 3))
    return usedMem

def get_Usr():
    users = psutil.users()
    if users:
        usr = users[0].name
    else:
        usr = "Unknown"
    return usr

def get_Battery():
    battery = psutil.sensors_battery()
    if battery:
        battery = round(battery.percent)
    else:
        battery = "Unknown"
    return battery

def generate_MatrixArt():
    # ASCII Art - Zero Matrix
    artMatrix = [[0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0]]

    # Flag for If Random Art Is Empty
    emptyMatrix = True

    # Randomly set a value for the ASCII Art Matrix
    for i in range(len(artMatrix)):
        for j in range(len(artMatrix[i])):

            if random.randint(0, 1) == 1:
                artMatrix[i][j] = 1

    # Replace 1's and 0's with colors
    coloredMatrix = []
    for i in range(len(artMatrix)):
        row = []
        hasColor = False  # Flag to track if the row has any colored elements
        for j in range(len(artMatrix[i])):

            if artMatrix[i][j] == 1:
                row.append(colored('███', colors[random.randint(0, 7)]))
                emptyMatrix = False
                hasColor = True

            else:
                row.append(colored('   ', 'white'))

        if not hasColor:
            row.append(colored('   ', 'white'))  # Add a default value to the row if no colors present

        coloredMatrix.append(row)

    # Redraw Art Matrix If Matrix Is Empty
    if emptyMatrix:
        return generate_MatrixArt()
    else:
        return coloredMatrix

def generate_ColorStrip():

    # Printing Color Spectrum (Bright Colors)
    i = 0
    while i < 7:

        if i == 0:
            print("  ", end='', sep='')

        x = colored('███', colors[i])
        print(x, end='', sep='')

        i += 1

        if i == 7:
            print("")

    # Printing Color Spectrum (Dim Colors)
    j = 0
    while j < 7:

        if j == 0:
            print("  ", end='', sep='')

        x = colored('███', colors[j])
        print(Style.DIM + x, end='', sep='')
        
        j += 1

        if j == 7:
            print("")



# Print Matrix Art
resultMatrix = generate_MatrixArt()

for row in resultMatrix:
    print("  ", "".join(row), "\n", end='', sep='')


# Printing Sys Info
print(f"    User: {get_Usr()}")
print(f"    Distro: {get_Distro()}")
print(f"    Kernel: {get_OS()} | {get_Xver()}")
print(f"    Memory*: {get_SysMemoryUsed()}GB / {get_SysMemoryTotal()}GB")
print(f"    Battery: {get_Battery()}%")


# Gather script arguments
args = sys.argv

# Checks for Color Strip  args
try:
    if len(args) > 1:
        if args[1] == "-cs" or args[1] == "--cs":
            generate_ColorStrip()
        else:
            raise ValueError("Incorrect argument")
    else:
        raise IndexError("Missing argument")

# If there are no ags commands, then don't show error
except IndexError:
    pass

# If garbage args are given
except ValueError:
    print(colored("Incorrect argument. Please use '-cs' to display a color strip.", "red"))