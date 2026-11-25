param([switch]$BuildOnly)
$ErrorActionPreference = 'Stop'
$ProjectRoot = Split-Path -Parent $PSScriptRoot
$Compiler = 'C:\MinGW\bin\g++.exe'
$Source = Join-Path $ProjectRoot 'src\Lab 5,6.cpp'
$Output = Join-Path $ProjectRoot 'src\Lab 5,6.exe'
$Include = Join-Path $ProjectRoot 'external\freeglut\include'
$Library = Join-Path $ProjectRoot 'external\freeglut\lib'
$Dll = Join-Path $ProjectRoot 'external\freeglut\bin\libfreeglut.dll'
$Data = Join-Path $ProjectRoot 'src\dino.dat.txt'
foreach ($Required in @($Compiler, $Source, $Include, $Library, $Dll, $Data)) {
    if (-not (Test-Path -LiteralPath $Required)) { throw "Missing required path: $Required" }
}
& $Compiler '-std=c++11' '-Wall' '-Wextra' '-g' $Source "-I$Include" "-L$Library" '-lfreeglut' '-lglu32' '-lopengl32' '-o' $Output
if ($LASTEXITCODE -ne 0) { throw 'Compilation failed. Close the previous lab window before rebuilding.' }
Copy-Item -LiteralPath $Dll -Destination (Join-Path $ProjectRoot 'src\libfreeglut.dll') -Force
Write-Host 'Build successful: src\Lab 5,6.exe'
if (-not $BuildOnly) { & $Output }
