# Title: TBD

This is currently a playground for Raylib on Windows

## Build Instructions (Windows)

1. Clone repository
1. Follow [Instructions to manually "install" W64Devkit](https://github.com/raysan5/raylib/wiki/Working-on-Windows#manual-setup-with-w64devkit)
1. Copy the following directories and file from **W64Devkit** into the repository:
	- `bin/`
	- `lib/`
	- `libexec/`
	- `x86_64-w64-mingw32/`
	- `w64devkit.exe`
1. Run `w64devkit.exe` to open a busybox shell
	- Navigate to the repository directory
	- Run the `make` command

If the above steps fail, copy all contents from **W64Devkit** to the repository directory, not just the minimal items outlined above.
