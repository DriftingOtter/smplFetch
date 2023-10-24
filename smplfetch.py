#!/usr/bin/env python3

import platform
import psutil
import random
import argparse
from colorama import init, Fore


init()



def get_Distro():
    return platform.node()



def get_OS():
    return f"{platform.system()} | {platform.machine()}"



def get_SysMemory():
    memory = psutil.virtual_memory()
    total_mem = round(memory.total / (1024**3))
    used_mem = round(memory.used / (1024**3))
    return used_mem, total_mem



def get_Usr():
    users = psutil.users()
    return users[0].name if users else "Unknown"



def get_Battery():
    battery = psutil.sensors_battery()
    return round(battery.percent) if battery else "Unknown"



def generate_MatrixArt(rows=3, cols=5):
    colors = [Fore.RED, Fore.GREEN, Fore.YELLOW, Fore.BLUE, Fore.MAGENTA, Fore.CYAN, Fore.WHITE]
    artMatrix = [[random.choice([0, 1]) for _ in range(cols)] for _ in range(rows)]
    emptyMatrix = all(all(cell == 0 for cell in row) for row in artMatrix)

    coloredMatrix = []
    for row in artMatrix:
        coloredRow = [
            random.choice(colors) + "███" if cell == 1 else Fore.WHITE + "  "
            for cell in row
        ]
        coloredMatrix.append(coloredRow)

    if emptyMatrix:
        return generate_MatrixArt(rows, cols)
    else:
        return coloredMatrix



def generate_ColorStrip():
    colors = [Fore.BLACK, Fore.RED, Fore.GREEN, Fore.YELLOW, Fore.BLUE, Fore.MAGENTA, Fore.CYAN, Fore.WHITE]

    for i in range(1): # Bright and dim colors
        print("  ", end="")
        for color in colors:
            print(color + "███", end="")
        print()



def main():
    parser = argparse.ArgumentParser(description='Display system information.')
    parser.add_argument('-cs', '--colorstrip', action='store_true', help='Display a color strip.')

    args = parser.parse_args()


    # Print Matrix Art
    resultMatrix = generate_MatrixArt()

    for row in resultMatrix:
        print("  ", "".join(row), "\n", end="")


    # Printing Sys Info
    used_mem, total_mem = get_SysMemory()
    print(f"    User: {get_Usr()}")
    print(f"    Distro: {get_Distro()}")
    print(f"    Kernel: {get_OS()}")
    print(f"    Memory*: {used_mem}GB / {total_mem}GB")
    print(f"    Battery: {get_Battery()}%")


    # Check for color strip flag
    if args.colorstrip:
        generate_ColorStrip()


if __name__ == "__main__":
    main()

