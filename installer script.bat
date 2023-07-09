@echo off
echo %time% Installation Starts


:adminCheck
openfiles 1>Nul 2>Nul
if errorlevel 1 goto runAs
goto stuff

:runAs
powershell "start installer.bat -v runAs"
exit


:stuff
cd /D %~dp0

reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\AppModelUnlock" /t REG_DWORD /f /v "AllowDevelopmentWithoutDevLicense" /d "1"
powershell -Command "add-appxpackage -path data/AppxManifest.xml -register"