#!/bin/bash

set -euo pipefail

DYLD_LIBRARY_PATH=./3rdparty/python_interpreter ./bazel-bin/main
