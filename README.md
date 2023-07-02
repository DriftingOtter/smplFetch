![smpleFetch](https://github.com/DriftingOtter/smplfetch/blob/main/smplfetch_Useage.png)
```
How it looks to run the script...
(on the left terminal, it shows the script with the additional arg for a color strip)*
```

# smplFetch 🍎
a simple python fetch script for linux.
with some cool art :)*

## How is it differnt from other fetch scripts?
Even though this script was made only for me it still has some cool things I wanted to share, like the randomly genereated matrix art.

## Compatability
It only works on linux as for right now, but I may add support for windows some time later if I have time.

## Rebuilds?
Yes, I will probably rebuilding another version of this script in C once I have fully learned it.

___Also maybe in Rust if I feel up to it...___

## How to run the script without going into script directory?

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

## Authors
Daksh Kaul (aka. me) 🦦
