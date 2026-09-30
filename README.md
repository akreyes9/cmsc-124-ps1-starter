<!--no-pdf-->
# CMSC 124 Problem Set 1 Starter

This incomplete C17 project is the starter for the ten data types from Unit 5.
This README gives the repository map, commands, starter baseline, supported
toolchains, and local verification details for the work that the manual defines.

## Pair

Replace the two entries below. An assigned trio adds one entry.

- Jemarco Briz (`@Jmbriz123`)
- Aleigha Keight Laranja Reyes (`@akreyes9`)

## Files You May Change

You may change only these files:

- The ten `src/dt_*.c` files
- `ANALYSIS.md`
- The Pair section in this README

Email `reflection.txt` separately. Do not add it to the repository.

Keep this list nearby while you work.

## Layout

```
include/dt.h              fixed public interface. Do not edit.
src/main.c                complete program entry point
src/driver.c              complete case-file front end
src/driver.h              complete driver interface. Do not edit.
src/print.c               complete output functions
src/dt_*.c                ten files that you must implement
cases/                    complete grading corpus
ANALYSIS.md               joint analysis that you must create
README.md                 fill the Pair section only
build.sh  run  check.sh   course run interface
```

## Commands

```bash
./build.sh          # Create one clean build in build/.
./run <case-file>   # Run one case file.
./check.sh          # Run the build, corpus, and sanitizer checks.
```

`check.sh` is the complete public automated check. No hidden test script
exists. The rubric also assesses analysis, collaboration history, and memory
evidence.

## Exit Codes

The laboratory interpreter uses the same exit-code contract.

| Code | Meaning |
|---|---|
| 0 | Every command ran. The program released each reference. |
| 65 | The driver rejected the case file before execution. |
| 70 | A command ran and reported an error. |

## First Run

A fresh clone builds without warnings. It passes 33 of 63 checks and exits 1.

Most passing cases expect an error. A stub that rejects every request can pass
these cases by accident. For example, `boundary/array_index_above_upper`
expects exit 70. The `dt_array_get` stub always returns `DT_ERR_RANGE`, which
produces exit 70.

The 33 passing checks do not show half completion. All ten `normal/` cases
fail. Implement the modules until those cases pass.

The workflow in the Actions tab also fails before implementation. This state
is correct for the starter. Your fork passes after you implement all modules.

## Tested Toolchains

Each row records an executed test.

| Environment | Versions | Result |
|---|---|---|
| MSYS2 UCRT64 on Windows 11 | GCC 16.2.0, CMake 4.4.2, Ninja 1.13.2, Python 3.14.7 | The starter passed 33 of 63 checks. The reference passed 63 of 63 checks. Sanitizers were unavailable. |
| Ubuntu 24.04 under WSL 2 | GCC 13.3.0, CMake 4.4.3, Ninja 1.13.2, Python 3.12.3 | The reference passed 63 of 63 checks twice. The sanitizer run and both private helpers passed. |
| GitHub Actions on `ubuntu-latest` | `.github/workflows/test.yml` | The current 63-case starter reached `check.sh` and produced the expected failure. |
| GitHub Actions on `macos-latest` | `.github/workflows/test.yml` with Apple Clang | The current 63-case starter reached `check.sh` and produced the expected failure. |

The Ubuntu WSL test used the same `verify.sh` entry point. CMake built the
MSYS2 test. An instructor reference supplied the complete implementation.

## Sanitizer Check

`check.sh` tests whether the compiler can link AddressSanitizer and
UndefinedBehaviorSanitizer. It runs the corpus again when both sanitizers are
available.

MinGW GCC does not include `libasan` or `libubsan`. The probe fails on MSYS2.
The script reports a skip. UCRT64 GCC 16.2.0 and mingw32 GCC 16.1.0 both show
this result. Your code cannot change this toolchain limit.

The GitHub Actions workflow runs both sanitizers on Ubuntu and macOS. Read both
jobs before submission. The Ubuntu job also checks for memory leaks.

Apple AddressSanitizer does not include a leak checker. Linux
AddressSanitizer enables leak detection by default.

The sanitizer check detects faults that output comparisons cannot detect.
During development, it found a leak in `driver.c`. A malformed quoted string
caused `scan_line` to abandon tokens from that line. All output checks passed
despite the leak.
