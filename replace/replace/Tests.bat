@echo OFF

SET PROGRAM="%~1"

if %PROGRAM%=="" (
	echo Plese specify path to program
	exit /B 1
)

rem пустой файл и пустые строки
%PROGRAM% testData\empty.txt "%TEMP%\output.txt" "" "" || goto err
fc testData\empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

rem искомая строка пустая
%PROGRAM% testData\test1.txt "%TEMP%\output.txt" "" 2 || goto err
fc testData\test1.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

rem пример из задания
%PROGRAM% testData\test1.txt "%TEMP%\output.txt" 1231234 6 || goto err
fc testData\test1result.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

rem замена на пустую строку
%PROGRAM% testData\test2.txt "%TEMP%\output.txt" "is" "" || goto err
fc testData\test2result.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

rem самый обычный тесет
%PROGRAM% testData\test3.txt "%TEMP%\output.txt" "simple" "hard" || goto err
fc testData\test3result.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 passed

rem тест с мамой
%PROGRAM% testData\test4.txt "%TEMP%\output.txt" "ma" "mama" || goto err
fc testData\test4result.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed

rem открытие несуществующего файла
%PROGRAM% MissingFile.txt "%TEMP%\output.txt" "" "" > nul && goto err
echo Test 7 passed

rem неверное количество аргументов
%PROGRAM% > nul && goto err
echo Test 8 passed

echo All test passed successfuly
exit /B 0

:err 
echo Test failed
exit /B 1