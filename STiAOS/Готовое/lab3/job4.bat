@echo off
SETLOCAL EnableDelayedExpansion
chcp 1251 >nul
SET fileName=%1
if not exist %fileName%.txt (
echo ������� ���� �� ������
) else (
Set Rar="C:\Program Files\WinRar\WinRar.exe" a -m5
"C:\Program Files\WinRar\WinRar.exe" a -m5 "%fileName%.rar" "%fileName%.txt"
pause
)