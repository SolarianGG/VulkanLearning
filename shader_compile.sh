#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

for i in ${SCRIPT_DIR}/shaders/*.vert
do
    glslc $i -o ${i}.spv
done

for i in ${SCRIPT_DIR}/shaders/*.frag
do
    glslc $i -o ${i}.spv
done