# Find-the-cat

##Context

This is a 2 months project done in the first semester of my second year at Télécom Nancy. The objective is to emulate the "find" command and implement multiple flag.

## How to use ?

Once the repository is imported, in the same folder as the makefile, simply type :
```bash
make
```

An object file called ftc has been generated, you can use it like the "find" command.
For example :
```bash
./ftc /home/usr/Download -size +9k -date -2d
```

It will print the same things as the "find" command with the same flag.

## Flag implemented :

Currently, here are the flags available :

- test : for debug purposer, print the value of the next flag
- name : exact value or regex
- date : (+|=|-) modifier, if not specified, the more recent file will be considered. Size modifier include : m (minutes), h (hours), j (day)
- size : (+|=|-) modifier, if not specified, the file with the exact size will be considered. Size modifier include : c (1), k (1024), M (1048576), G (1073741824)
- mime : return the file with the same mime type, leverang the MegaMime library from Owen Trump, see MIT license : lib/Megamimes.h
- ctc : catch the cat, search inside text file if a pattern is present ( simulate the grep -rl [pattern] [directory] command )
- dir : return only directory

## Verification

A simple way to check if everythings is working, you can use the command :

```bash
find /home/usr/Download -name *.exe d | wc -l
./ftc /home/usr/Download -name *.exe | wc -l
```

The same number should appear.



