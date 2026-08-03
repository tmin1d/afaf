$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSScriptRoot
$envFile = Join-Path $root ".env"
$supabaseDir = Join-Path $root "web/supabase"

if (-not (Test-Path $envFile)) {
  throw ".env file not found: $envFile"
}

Get-Content $envFile | ForEach-Object {
  $line = $_.Trim()

  if ($line.Length -eq 0 -or $line.StartsWith("#")) {
    return
  }

  $name, $value = $line -split "=", 2

  if ($name -and $value -ne $null) {
    [Environment]::SetEnvironmentVariable($name.Trim(), $value.Trim(), "Process")
  }
}

if (-not $env:SUPABASE_ACCESS_TOKEN) {
  throw "SUPABASE_ACCESS_TOKEN is empty in .env"
}

if (-not $env:SUPABASE_PROJECT_REF) {
  throw "SUPABASE_PROJECT_REF is empty in .env"
}

Push-Location $supabaseDir
try {
  supabase functions deploy esp32-wifi --project-ref $env:SUPABASE_PROJECT_REF
}
finally {
  Pop-Location
}
