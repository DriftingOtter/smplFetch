import platform
import psutil


from colorama import init, Style
from termcolor import colored
init()


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


colors = ['black', 'red', 'green', 'yellow', 'blue', 'magenta', 'cyan', 'white']


print(f"| User: {get_Usr()}")
print(f"| Distro: {get_Distro()}")
print(f"| Kernel: {get_OS()} | {get_Xver()}")
print(f"| Memory*: {get_SysMemoryUsed()}GB / {get_SysMemoryTotal()}GB")
print(f"| Battery: {get_Battery()}%")
print("")

i = 0
while i < 7:

    if i == 0:
        print("  ", end='', sep='')

    x = colored('███', colors[i])
    print(x, end='', sep='')
    i += 1

    if i == 7:
        print("")


j = 0
while j < 7:

    if j == 0:
        print("  ", end='', sep='')

    x = colored('███', colors[j])
    print(Style.DIM + x, end='', sep='')
    j += 1

    if j == 7:
        print("")
