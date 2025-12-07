# Student Record Management System

A simple student record management project that includes:

- `gui.py` — a Python Tkinter-based GUI for adding, updating, deleting and searching student records. Data is saved to `students.json` in the project directory.
- `student_backend.cpp` — a small C++ program that reads `students.json`, computes statistics (average age, standard deviation, counts by major/grade, youngest/oldest), and writes a detailed report to `student_report.txt`.
- `student_backend.exe` — a prebuilt Windows executable of the C++ backend (if present).

## Features

- Add / update / delete student records from a friendly GUI.
- Persistent storage in `students.json` (created automatically by the GUI).
- Search & display students in a table view.
- Generate a text report with statistics using the C++ backend.

## Prerequisites

- Windows (tested)
- Python 3.6+ (3.8+ recommended)
  - `tkinter` (usually included with standard Python installers on Windows)
- (Optional) A C++ compiler like `g++` (MinGW) or Visual Studio if you want to build `student_backend.exe` from source.

## Files of interest

- `gui.py` — the Python GUI application. Run this to manage student records and create/update `students.json`.
- `students.json` — data file created/used by the GUI. Keep it in the same directory as the programs.
- `student_backend.cpp` — C++ source for generating statistical reports.
- `student_backend.exe` — prebuilt executable (Windows) if already present.

## How to run

1) Run the GUI (recommended for day-to-day use):

```powershell
# From the project directory
python gui.py
```

The GUI will create `students.json` (if it doesn't exist) and save records there. Use the GUI buttons to Add / Update / Delete / Clear fields. Use the search box to filter results.

2) Generate a report with the C++ backend

- Use the provided `student_backend.exe` (if present):

```powershell
# Ensure students.json exists in the same folder (created by the GUI)
.\student_backend.exe
```

- Or, build from source with g++ (MinGW) and run:

```powershell
# Build (run from project folder)
g++ student_backend.cpp -o student_backend.exe
# Then run
.\student_backend.exe
```

When run, the C++ program reads `students.json`, prints a statistics summary to the console, and writes a detailed table to `student_report.txt`.

## Notes and caveats

- The GUI stores data in `students.json` using JSON arrays of student objects. The C++ parser in `student_backend.cpp` implements a simple, tolerant parser that expects the JSON object-per-student format produced by `gui.py`. If you hand-edit `students.json`, try to preserve a standard JSON object array structure.
- If `students.json` is missing or empty, the C++ program will report "No students found or error reading file!" and exit with code 1. Use the GUI to add records first.
- The GUI performs basic validation (required fields, numeric age between 0 and 150). The C++ program attempts to parse integers for age and will default invalid ages to 0 with a warning.

## Troubleshooting

- "tkinter not found" — ensure you installed Python from the official installer that includes Tcl/Tk support. Reinstall or use the Windows installer from python.org.
- Permission issues when creating `students.json` or `student_report.txt` — run from a directory where you have write permissions (e.g., your user Documents folder).
- If the provided `student_backend.exe` doesn't run on your system, build from `student_backend.cpp` using MinGW or Visual Studio.

## License

This repository does not include a license file. If you want to reuse or redistribute this project, consider adding an appropriate license (for example, MIT) to clarify terms.

## Next steps / Improvements

- Add unit tests for the JSON parsing and report generation (C++).
- Improve the C++ JSON parsing by using a standard library like `nlohmann/json`.
- Add packaging or an installer for the GUI on Windows.

---

If you'd like, I can also:
- Add a small `requirements.txt` or `pyproject.toml` for the Python side.
- Create a Windows batch or PowerShell script to build/run the C++ backend automatically.
- Add an explicit license file.

Tell me which of those you'd like me to do next.