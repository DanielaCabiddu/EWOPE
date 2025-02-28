#!/bin/sh

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

${SCRIPT_DIR}/../../build-Linux/EWOPE_data -i ${SCRIPT_DIR}/../data/in/samples_sec4000.csv -S --setX 0 --setY 1 --setZ 2 -C -o ${SCRIPT_DIR}/../data/out