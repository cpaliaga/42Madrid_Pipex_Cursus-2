#! /bin/sh
git pull
git add .
git commit -m $(date -u | tr ' ' '_')
git push
