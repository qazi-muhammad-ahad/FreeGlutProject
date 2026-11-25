# Project handoff

## 2026-11-25: FreeGLUT shapes and 2D transforms

- Objective: replace the quad in `src/main.cpp` with individually callable n-gon, rosette, circle, and triangle routines, add reusable 2D transformations, and verify compilation.
- Inspected current source and build configuration. The existing `scripts/build-run.ps1` links OpenGL without GLU.
- Read manual PDF pages 39–43 and 45 for regular polygon vertices, rosette vertex pairs, circle sampling, and modelview transformations.
- Implemented all four outline drawing routines in `src/main.cpp`. The display defaults to a centered hexagon. Modelview helpers support translation, rotation in degrees, and independent X/Y scaling. The orthographic projection uses core OpenGL for compatibility with the existing build script.
- Validation: `git diff --check -- src/main.cpp` passed. MinGW compiled and linked with bundled FreeGLUT and OpenGL using `-std=c++11 -Wall -Wextra -pedantic` without diagnostics. Windows blocked sandboxed compiler startup with a DLL relocation error, and the approved retry succeeded. The temporary test executable was removed.
- Runtime rendering was not checked. No pending operations. To select a different shape, replace the draw call in `display()` and rebuild.

Updated: 2026-10-15

## Latest revision: manual code (supersedes implementation notes below)
- User explicitly requested immediate correction after reserve stop; treated as a bounded override for this correction and build only.
- Rewrote src/Lab 5,6.cpp around the manual's myMouse, setWindow, setViewport, sinc loop, 5x5 tiling loop with 64x44 viewports, and page-22 drawPolyLineFile. Three manual-selection setup calls remain in main.
- Documented adaptations: offset/smaller viewport requested by user; sinc zero guard; drawDot helper flips mouse y; reader takes const char*; reader's glClear moved outside tile loop so earlier tiles survive; actual dino.dat.txt filename; executable-directory working-directory setup. Single buffering with glFlush matches manual. Dots now follow manual's immediate drawing and may disappear on repaint. Tiles occupy 320x220 pixels as in the manual, not the full 800x600 window.
- Added -lglu32 in scripts/run-lab5-6.ps1, .vscode/tasks.json and .vscode/settings.json for the manual's gluOrtho2D.
- Validation: revised scripts/run-lab5-6.ps1 -BuildOnly succeeded with no warnings reported; executable rebuilt and DLL prepared. Interactive/visual validation remains unperformed. No processes pending.
- Next actions when quota permits or explicitly authorized: run all three manual selections, verify mouse positions, offset sinc viewport and all 25 dinosaur tiles, rebuilding for each selection; restore lab5MouseDots default. No additional feature work authorized by the bounded reserve override.

## Earlier Lab 5 and 6 implementation (superseded)
- Request: src/Lab 5,6.cpp with three exercises selected manually in main: mouse dots, offset/resized viewport, and dinosaur tiles.
- Read manual PDF pages 24-29: mouse dots use left clicks and right-click exit; viewport example plots sinc; tiling repeats dinosaur in 5 by 5 viewports.
- Added src/Lab 5,6.cpp: select exactly one of lab5MouseDots(), lab6Viewport(), or lab6DinosaurTiles() in main. Dots persist on repaint; viewport plots sinc with zero handled; dinosaur tiles use 25 viewports and load src/dino.dat.txt relative to executable. Shared reshape callback supports window resizing.
- Added scripts/run-lab5-6.ps1 with optional -BuildOnly, existing MinGW/FreeGLUT paths, quoted file arguments, and runtime DLL copying. Existing VS Code active-file build also supports this source. Existing debugger configuration remains unchanged.
- Validation: scripts/run-lab5-6.ps1 -BuildOnly succeeded, compiling/linking all functions with -std=c++11 -Wall -Wextra, no warnings reported. Output src/Lab 5,6.exe and runtime DLL prepared. Sandboxed compiler startup encountered Windows DLL relocation error; approved execution outside sandbox succeeded.
- Not run: interactive startup, click/repaint/resize checks, and visual checks for viewport/tiles; dinosaur loader not exercised at runtime. PDF relevant pages extracted as text, not rendered.
- Stop reason: account reserve threshold reached after successful build. No pending processes or further changes in flight.
- Exact next actions when quota permits: run default dots mode and verify left-click placement/repaint and right-click exit; select lab6Viewport in main, rebuild, inspect plot; select lab6DinosaurTiles, rebuild, launch from project root to verify executable-relative loading and 25 tiles; restore default dots mode and rebuild. Do not claim these runtime checks passed until performed.

- Objective: inspect the directory and explain its setup, connections, compilation, and execution briefly. Static inspection complete.
- Reviewed all application sources, both dinosaur datasets, scripts/build-run.ps1, and .vscode configuration; inventoried bundled FreeGLUT headers, x86/x64 libraries and DLLs, executables, and object files.
- Each src/*.cpp is a separate program with its own main and GLUT display callback. main.cpp draws a rainbow circle; lab2.cpp currently draws a scaled dinosaur; Lab4.cpp currently draws three transformed houses and includes wave/dinosaur exercises; test.cpp is a basic quad experiment. src/GP_Mid.cs is empty and was already untracked.
- Default VS Code build compiles the active file with MinGW g++, links freeglut and opengl32, and copies the runtime DLL beside its executable. scripts/build-run.ps1 specifically builds and launches src/main.cpp. Bundled non-x64 libraries are selected by these configurations.
- Dinosaur loaders read relative filenames, requiring src as the working directory. The datasets contain polyline counts, point counts, and coordinates; the spikes variant modifies the outline.
- .vscode/launch.json retains an old absolute checkout path and an outDebug target, rather than the task-generated executables. Debugging configuration needs adjustment if requested. test.cpp lacks buffer swapping despite selecting double buffering and uses coordinates outside the default clip space.
- Validation: read source/configuration/data; confirmed configured g++ path exists; inspected git status. No builds, executable launches, or runtime/visual tests performed. Binary contents and third-party library implementation were not audited.
- Pending operations/blockers: none for this analysis request. No application changes made.
- Next action if execution is requested: build the desired source separately, run from src for dinosaur data, and align debugger program/cwd with that executable.
