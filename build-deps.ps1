# Builds the two libraries RAFGL.cbp links against, and drops them where it
# expects them:
#
#   libs/glfw/libglfw3.a            (static)
#   libs/assamp/lib/libassimp.dll.a (import lib for libassimp-5.dll)
#
# Also replaces the stale bundled headers in include/ (GLFW 3.3.0 and
# Assimp 3.3.x) with headers matching the libraries built here. Originals are
# backed up to include/GLFW.bak and include/assimp.bak on first run.
#
# Run from PowerShell:   .\build-deps.ps1

$ErrorActionPreference = "Stop"

$Project = "C:\Users\Luka\Downloads\opengl-terrain-simulation"
$Deps    = "C:\Users\Luka\Downloads\gl-deps"
$MinGW   = "C:\Program Files\CodeBlocks\MinGW\bin"

$env:Path = "$MinGW;" + $env:Path

$GlfwTag   = "3.4"
$AssimpTag = "v5.4.3"

Write-Host "==> toolchain"
& gcc --version | Select-Object -First 1
& cmake --version | Select-Object -First 1

New-Item -ItemType Directory -Force -Path $Deps | Out-Null

# ---------------------------------------------------------------- GLFW ------
Write-Host "==> fetching GLFW $GlfwTag"
if (-not (Test-Path "$Deps\glfw")) {
    git clone --depth 1 --branch $GlfwTag https://github.com/glfw/glfw.git "$Deps\glfw"
}

Write-Host "==> configuring GLFW (static)"
cmake -S "$Deps\glfw" -B "$Deps\build-glfw" -G Ninja `
    -DCMAKE_BUILD_TYPE=Release `
    -DCMAKE_C_COMPILER=gcc `
    -DBUILD_SHARED_LIBS=OFF `
    -DGLFW_BUILD_EXAMPLES=OFF `
    -DGLFW_BUILD_TESTS=OFF `
    -DGLFW_BUILD_DOCS=OFF `
    -DCMAKE_INSTALL_PREFIX="$Deps\install-glfw"

Write-Host "==> building GLFW"
cmake --build "$Deps\build-glfw" --parallel
if ($LASTEXITCODE -ne 0) { throw "GLFW build failed (exit $LASTEXITCODE)" }
cmake --install "$Deps\build-glfw"
if ($LASTEXITCODE -ne 0) { throw "GLFW install failed (exit $LASTEXITCODE)" }

# -------------------------------------------------------------- Assimp ------
Write-Host "==> fetching Assimp $AssimpTag"
if (-not (Test-Path "$Deps\assimp")) {
    git clone --depth 1 --branch $AssimpTag https://github.com/assimp/assimp.git "$Deps\assimp"
}

# Built SHARED on purpose: RAFGL.cbp links libassimp.dll.a, which is the
# import library for a DLL. A static build would not produce it.
#
# This project only ever loads .obj models, so all other importers are off --
# that cuts the build from ~10 min to ~2. To support more formats later, drop
# the two ASSIMP_BUILD_*_IMPORTER lines below.
#
# ASSIMP_NO_EXPORT is required, not just an optimisation: the glTF and FBX
# exporters reference types owned by their matching importers, so building
# them with the importers disabled fails to compile. We only ever read models.
Write-Host "==> configuring Assimp (shared, OBJ importer only, no exporters)"
cmake -S "$Deps\assimp" -B "$Deps\build-assimp" -G Ninja `
    -DCMAKE_BUILD_TYPE=Release `
    -DCMAKE_C_COMPILER=gcc `
    -DCMAKE_CXX_COMPILER=g++ `
    -DBUILD_SHARED_LIBS=ON `
    -DASSIMP_BUILD_TESTS=OFF `
    -DASSIMP_BUILD_ASSIMP_TOOLS=OFF `
    -DASSIMP_INSTALL=ON `
    -DASSIMP_BUILD_ZLIB=ON `
    -DASSIMP_WARNINGS_AS_ERRORS=OFF `
    -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=OFF `
    -DASSIMP_BUILD_OBJ_IMPORTER=ON `
    -DASSIMP_NO_EXPORT=ON `
    -DASSIMP_BUILD_USE_CCACHE=OFF `
    -DCMAKE_INSTALL_PREFIX="$Deps\install-assimp"

Write-Host "==> building Assimp"
cmake --build "$Deps\build-assimp" --parallel
if ($LASTEXITCODE -ne 0) { throw "Assimp build failed (exit $LASTEXITCODE)" }
cmake --install "$Deps\build-assimp"
if ($LASTEXITCODE -ne 0) { throw "Assimp install failed (exit $LASTEXITCODE)" }

# ------------------------------------------------- place build artifacts -----
Write-Host "==> installing libraries into the project"
New-Item -ItemType Directory -Force -Path `
    "$Project\libs\glfw", `
    "$Project\libs\assamp\lib", `
    "$Project\bin\Debug", `
    "$Project\bin\Release" | Out-Null

Copy-Item "$Deps\install-glfw\lib\libglfw3.a" "$Project\libs\glfw\libglfw3.a" -Force

# Normalise the import-lib name to exactly what RAFGL.cbp asks for.
$assimpImportLib = Get-ChildItem "$Deps\install-assimp\lib\libassimp*.dll.a" | Select-Object -First 1
Copy-Item $assimpImportLib.FullName "$Project\libs\assamp\lib\libassimp.dll.a" -Force

# Windows resolves DLLs relative to the .exe, not the working directory,
# so the runtime DLL goes beside the binaries -- not in the project root.
$assimpDll = Get-ChildItem "$Deps\install-assimp\bin\libassimp*.dll" | Select-Object -First 1
Copy-Item $assimpDll.FullName "$Project\bin\Debug\" -Force
Copy-Item $assimpDll.FullName "$Project\bin\Release\" -Force

# ------------------------------------------------------ refresh headers ------
# include/ is on the compiler's search path, so the stale 3.3.x Assimp headers
# would shadow the new ones and mismatch the library we just built.
Write-Host "==> replacing stale headers (backups: *.bak)"
if (-not (Test-Path "$Project\include\GLFW.bak"))   { Copy-Item "$Project\include\GLFW"   "$Project\include\GLFW.bak"   -Recurse }
if (-not (Test-Path "$Project\include\assimp.bak")) { Copy-Item "$Project\include\assimp" "$Project\include\assimp.bak" -Recurse }

Remove-Item "$Project\include\GLFW", "$Project\include\assimp" -Recurse -Force
Copy-Item "$Deps\install-glfw\include\GLFW"     "$Project\include\GLFW"   -Recurse
Copy-Item "$Deps\install-assimp\include\assimp" "$Project\include\assimp" -Recurse

# ---------------------------------------------------------------- done ------
Write-Host ""
Write-Host "==> done"
Get-Item "$Project\libs\glfw\libglfw3.a", "$Project\libs\assamp\lib\libassimp.dll.a" | Format-Table Name, Length
Get-ChildItem "$Project\bin\Debug\libassimp*.dll" | Format-Table Name, Length

Write-Host ""
Write-Host "Next: open RAFGL.cbp in Code::Blocks and Build & Run."
Write-Host "NOTE: it will still crash at main.cpp:90 until test/tree.obj,"
Write-Host "      test/grassModel.obj and test/lamp.obj exist."
