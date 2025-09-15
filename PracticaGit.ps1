# ==============================
# CONFIGURACIÓN
# ==============================
# URL del repositorio
$repoUrl = "https://github.com/J0SSU/Practica-C.git"

# Carpeta donde se clonará el repositorio
$localRepo = "C:\Scripts"

# Directorios dentro del repositorio
$srcDir = Join-Path $localRepo "SRC"
$binDir = Join-Path $localRepo "BIN"

# ==============================
# 1. Clonar el repositorio
# ==============================
if (Test-Path $localRepo) {
    Write-Host "El repositorio ya existe en $localRepo, actualizando..."
    Set-Location $localRepo
    git pull origin master
} else {
    Write-Host "Clonando el repositorio..."
    git clone $repoUrl $localRepo
    Set-Location $localRepo
}

# ==============================
# 2. Compilar archivos .c
# ==============================
if (-not (Test-Path $binDir)) {
    New-Item -ItemType Directory -Path $binDir | Out-Null
}

$files = Get-ChildItem -Path $srcDir -Filter *.c

foreach ($file in $files) {
    $exeName = [System.IO.Path]::GetFileNameWithoutExtension($file.Name) + ".exe"
    $exePath = Join-Path $binDir $exeName

    Write-Host "Compilando $($file.Name) -> $exeName"

    gcc $file.FullName -o $exePath

    if (Test-Path $exePath) {
        Write-Host "Ejecutable generado en $exePath"

        # ==============================
        # 3. Subir el .exe a GitHub
        # ==============================
        git add $exePath
        git commit -m "Agregado ejecutable $exeName compilado automáticamente"
        git push origin master
    } else {
        Write-Host "Error compilando $($file.Name)"
    }
}