# Focas: A Programming Launguage

Focas is a programming language that can be transcompiled to C++ and run. You can also embed C++ code, so you can do anything you can do with C++. It can also be written more concisely than C++. For more information, please read this README.

## Installation

To install focas, execute these commands.

If you use **Linux or Mac**
```
$ git clone https://github.com/natsuakane/Focas.git
$ cd Focas
$ ./setup_linux_or_mac.sh
```

If you use **Windows**
```
> git clone https://github.com/natsuakane/Focas.git
> cd Focas
> ./setup_windows.ps1
```

## How To Use

You can transpile the .focas files into .cpp files by running the following command.

```
> focas FILENAME.focas
```
If you want to transpile multiple files at once
```
> focas -c FILENAME1.focas FILENAME2.focas
```
If you want to output a name
```
> focas -o OUTPUT_FILENAME.cpp INPUT_FILENAME.focas
```

If the -o option is not used, the output will be `{input filename}.cpp`.

## Documentation

To see the syntax of this language, see the docs/Reference.md file.

## Contribute

If you want to fix a bug or add a new feature, you are welcome to change the code.
