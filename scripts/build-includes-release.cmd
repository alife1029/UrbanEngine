@echo off
py build_includes.py -r %cd%\.. -o %cd%\..\bin\Release-windows\UrbanEngine
pause
