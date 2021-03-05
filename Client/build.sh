#!/bin/bash
pyinstaller -F main.py -i Icon.ico --noconsole
cp ./dist/main ./main.elf
rm -rf ./build ./dist __pycache__ main.spec
