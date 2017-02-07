#/bin/bash

SRC_PATH=./src/
OUT_PATH=./bin/
FILE_COUNT=0

touch .files
find $SRC_PATH -name *.cpp > .files

while read f;
  do
    IFS='/' read -r -a array <<< "$f"
    mkdir $OUT_PATH${array[2]} &> /dev/null

    F_BIN=${f/$SRC_PATH/$OUT_PATH}
    F_BIN=${F_BIN/.cpp/.out}
    echo "Compiling $f"
    g++ $f -o $F_BIN
    FILE_COUNT=$((FILE_COUNT + 1))
  done < .files

rm .files
echo "Compiled $FILE_COUNT files."
