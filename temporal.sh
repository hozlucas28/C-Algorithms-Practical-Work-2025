#!/bin/bash

git add .
git diff-index --quiet HEAD || git commit -m "ci: format code"