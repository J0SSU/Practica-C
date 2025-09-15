# Directorios
$srcDir = ".\SRC"
$binDir = ".\BIN"

# Crear carpeta bin si no existe
if (-not (Test-Path $binDir)) {
    New-Item -ItemType Directory -Path $binDir | Out-Null
}

# Buscar todos los .c en src
$files = Get-ChildItem -Path $srcDir -Filter *.c

foreach ($file in $files) {
    $exeName = [System.IO.Path]::GetFileNameWithoutExtension($file.Name) + ".exe"
    $exePath = Join-Path $binDir $exeName

    Write-Host "Compilando $($file.Name) -> $exeName"

    # Compilar con gcc
    gcc $file.FullName -o $exePath

    if (Test-Path $exePath) {
        Write-Host "$exeName generado en $binDir"
	C:\Scripts\BIN\cifrado.exe
    } else {
        Write-Host "Error compilando $($file.Name)"
    }
}