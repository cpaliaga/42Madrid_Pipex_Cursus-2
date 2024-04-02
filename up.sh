#! /bin/sh
git add .
git commit -m $(date -u | tr ' ' '_')
git push
