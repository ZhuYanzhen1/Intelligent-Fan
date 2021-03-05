@echo off
echo make sure that you have installed python3
pyinstaller -F .\main.py -i %~dp0Icon.ico --noconsole
copy %~dp0dist\main.exe %~dp0
rd/s/q %~dp0dist 
rd/s/q %~dp0build
rd/s/q %~dp0__pycache__
del %~dp0main.spec
echo Build Success!!!
pause


