$ErrorActionPreference = "Stop"

$ProjectRoot = Split-Path -Parent $PSScriptRoot

$Compiler = "C:\MinGW\bin\g++.exe"

$Source = Join-Path $ProjectRoot "src\main.cpp"
$Output = Join-Path $ProjectRoot "src\main.exe"

$IncludePath = Join-Path $ProjectRoot "external\freeglut\include"
$LibraryPath = Join-Path $ProjectRoot "external\freeglut\lib"

$DllSource = Join-Path $ProjectRoot "external\freeglut\bin\libfreeglut.dll"
$DllDestination = Join-Path $ProjectRoot "src\libfreeglut.dll"

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "      OpenGL / FreeGLUT Build" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Kill previous executable if it is still running
Get-Process "main" -ErrorAction SilentlyContinue |
    Stop-Process -Force -ErrorAction SilentlyContinue

# Validate required files/folders
if (-not (Test-Path $Compiler)) {
    Write-Error "g++ not found: $Compiler"
    exit 1
}

if (-not (Test-Path $Source)) {
    Write-Error "Source file not found: $Source"
    exit 1
}

if (-not (Test-Path $IncludePath)) {
    Write-Error "FreeGLUT include folder not found: $IncludePath"
    exit 1
}

if (-not (Test-Path $LibraryPath)) {
    Write-Error "FreeGLUT library folder not found: $LibraryPath"
    exit 1
}

if (-not (Test-Path $DllSource)) {
    Write-Error "FreeGLUT DLL not found: $DllSource"
    exit 1
}

# -------------------------------
# Build
# -------------------------------

Write-Host "[1/3] Compiling..." -ForegroundColor Yellow

& $Compiler `
    $Source `
    "-I$IncludePath" `
    "-L$LibraryPath" `
    "-lfreeglut" `
    "-lopengl32" `
    "-g" `
    "-o" `
    $Output

if ($LASTEXITCODE -ne 0) {
    Write-Error "Compilation failed."
    exit $LASTEXITCODE
}

Write-Host "Compilation successful." -ForegroundColor Green
Write-Host ""

# -------------------------------
# Copy DLL
# -------------------------------

Write-Host "[2/3] Copying FreeGLUT DLL..." -ForegroundColor Yellow

Copy-Item `
    $DllSource `
    $DllDestination `
    -Force

Write-Host "DLL copied successfully." -ForegroundColor Green
Write-Host ""

# -------------------------------
# Run
# -------------------------------

Write-Host "[3/3] Running application..." -ForegroundColor Yellow
Write-Host ""

& $Output