#!/bin/bash

git add .
if git diff-index --quiet HEAD || git commit -m "ci: format code"; then
    echo "true"
else
    echo "false"
fi