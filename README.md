# ReadSystematom

## Dependencies

```Bash
sudo pacman -Sy libserialport
```

## Building

```Bash
g++ main.cpp -lserialport -o readSystematom.elf
```

## Running

```Bash
./readSystematom.elf /dev/ttyS0
```
