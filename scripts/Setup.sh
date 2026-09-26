#!/usr/bin/env bash
# Usage: ./scripts/Setup.sh [debug|release|dist] [--no-run]
set -euo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")/.."

CONFIG="debug"
RUN_APP=true
for arg in "$@"; do
  case "${arg}" in
    debug|release|dist) CONFIG="${arg}" ;;
    --no-run) RUN_APP=false ;;
    *) echo "Usage: ./scripts/Setup.sh [debug|release|dist] [--no-run]"; exit 1 ;;
  esac
done

premake5 gmake
make "config=${CONFIG}" -j"$(sysctl -n hw.ncpu)"

if [[ "${RUN_APP}" == true ]]; then
  CONFIG_DIR="$(tr '[:lower:]' '[:upper:]' <<< "${CONFIG:0:1}")${CONFIG:1}"
  cd Daylight
  exec "../bin/${CONFIG_DIR}-macosx-AARCH64/Daylight/Daylight"
fi
