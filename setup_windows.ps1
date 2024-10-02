# Check if the script is running with administrator privileges
if (-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")){   
    Write-Warning "Please run this script as an Administrator!"
    Break
}

# Specify the source file name
$SourceFile = "bin\focas"

# Specify the destination directory (typically System32 folder for Windows)
$DestDir = "$env:windir\System32"

# Check if the source file exists
if (-not (Test-Path $SourceFile)) {
    Write-Error "Error: Source file $SourceFile not found."
    exit 1
}

# Copy the file
try {
    Copy-Item $SourceFile $DestDir -Force
    Write-Host "File $SourceFile successfully copied to $DestDir."

    # Update PATH if necessary
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + $DestDir
    [System.Environment]::SetEnvironmentVariable("Path", $env:Path, "Machine")
    Write-Host "PATH updated. New executables should now be available."
}
catch {
    Write-Error "Error: Failed to copy file. $_"
    exit 1
}