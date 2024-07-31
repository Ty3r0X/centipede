@echo off
setlocal

:: Set Windows SDK Version
set SDK_VERSION=10.0.26100.0
set WDK_VERSION=1.33

:: Set the Windows SDK and WDK paths
set SDK_DIR=C:\Program Files (x86)\Windows Kits\10
set WDK_DIR=C:\Program Files (x86)\Windows Kits\10

:: Set the paths for include and lib directories
set INCLUDE=%SDK_DIR%\Include\%SDK_VERSION%\km;%WDK_DIR%\Include\wdf\kmdf\%WDK_VERSION%
set LIB=%SDK_DIR%\Lib\%SDK_VERSION%\km\x64;%WDK_VERSION%\Lib\wdf\kmdf\x64\%WDK_VERSION%

:: Compilation
cl.exe /D NDIS_MINIPORT_DRIVER /D _X86_ /D WIN32_LEAN_AND_MEAN /D _AMD64_ /D _WIN32_WINNT=0x0A00 /I %INCLUDE% /Zi /W4 /WX /MD /c src\entrpoint.c /FoMyDriver.obj

:: Linking
link.exe /nologo /OUT:MyDriver.sys /SUBSYSTEM:NATIVE /ENTRY:DriverEntry /RELEASE /NODEFAULTLIB kernel32.lib MyDriver.obj

echo Build completed.
endlocal
