![smpleFetch](https://github.com/DriftingOtter/smplFetch/blob/main/smplFetch_C_Py.png)
```
How it looks to run the script...
(on the left it shows the C impl and on the right, Python*)
```

# smplFetch 🍎
a simple python fetch script for linux.
___with some cool headers :)___

## How is it different from other fetch scripts?
Even though this script was made only for me, it still has some cool things I wanted to share, like the randomly genereated matrix art for the python implementation, and a cool clock header for the C implementation. 
(these are subject to change based on my thoughts of what to add or change in the builds*)

## Compatability
It only works on linux as for right now, but I may add support for windows some time later if I have time.

## Rebuilds?
As of recent, I have rebuilt the fetch script in C with a new header (clock).
I will try to rebuilt this is any language I learn from now on as a quick and simple project :)

___Also maybe in Rust if I feel up to it...___

## How to run the script without going into script directory?

this can done similarly with the C file once compiled.
___(look at bottom of this section for the C compilation steps*)___

### Make a python script:
```
cd /home/el/bin
touch stuff.py
chmod +x stuff.py
```

### Find out where your python is:
```
which python
/usr/bin/python
```

### Put this code in there:
```
#!/usr/bin/python
print "hi"
```

### Run in it the same directory:
```
python stuff.py
```

### Go up a directory and it's not available:
```
cd ..
stuff.py

-bash: stuff.py: command not found
```

### Not found! It's as we expect, add the file path of the python file to the $PATH
```
vi ~/.bashrc
```

### Add the file:
```
export PATH=$PATH:/home/el/bin
```

### Save it out, re apply the .bashrc, and retry
```
source ~/.bashrc
```

### Try again:
```
cd /home/el
stuff.py
```

### Prints:
```
hi
```

___(if anyone can tell me the orginal person that wrote this response on StackOverflow that would be a great help. As I would like to give credit to them 😅)___

## Compilation Of The C Script
One you have cloned/downloaded the script file run...
```
gcc -o smplFetch smplfetch.c
```
You don't have to use gcc, use what ever you like for C compilation.

## Authors
- Daksh Kaul (aka. me) 🦦

## Acknowledgements
- fontawesome (for otter glyph) 

