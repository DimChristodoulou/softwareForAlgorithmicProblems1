#!/bin/bash
echo "$PWD"
doxygen Doxyfile
git config --global user.email "dchristodoulou.di@gmail.com"
git config --global user.name "DimChristodoulou"
git add . && \
git add -u && \
read -p "Commit description: " desc
git commit -m "$desc" && \
git push heroku master
cp "html/*" "../project-algorithms-doc"
cd "../project-algorithms-doc"
git add .
git commit -m "$desc"
git push
