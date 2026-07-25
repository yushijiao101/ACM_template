#!/usr/bin/env python3
"""Compile and run the repository's small standalone C++ tests."""

from pathlib import Path
import shutil
import subprocess
import sys


TEST_DIR = Path(__file__).resolve().parent
BUILD_DIR = TEST_DIR / ".build"


def main() -> int:
    compiler = shutil.which("g++")
    if compiler is None:
        print("[FAIL] g++ was not found in PATH")
        return 1

    test_files = sorted(TEST_DIR.glob("test_*.cpp"))
    if not test_files:
        print("[FAIL] no test_*.cpp files found")
        return 1

    BUILD_DIR.mkdir(exist_ok=True)
    failures = 0

    for source in test_files:
        executable = BUILD_DIR / f"{source.stem}.exe"
        compile_command = [
            compiler,
            "-std=c++17",
            "-Wall",
            "-Wextra",
            str(source),
            "-o",
            str(executable),
        ]
        compiled = subprocess.run(compile_command, capture_output=True, text=True)
        if compiled.returncode != 0:
            failures += 1
            print(f"[FAIL] compile {source.name}")
            print(compiled.stderr.rstrip())
            continue

        executed = subprocess.run([str(executable)], capture_output=True, text=True)
        if executed.returncode != 0:
            failures += 1
            print(f"[FAIL] run {source.name}")
            print((executed.stderr or executed.stdout).rstrip())
            continue

        print(f"[ OK ] {source.name}")

    print(f"\n{len(test_files) - failures}/{len(test_files)} tests passed")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
