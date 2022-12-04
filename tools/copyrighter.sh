#!/bin/bash

if [ -z "$1" ]
  then
    echo "You must supply your name as an argument."
    exit -1
fi

copyright_text="  Copyright (c) $(date +"%Y"), $1\n  All rights reserved.\n\n  This source code is licensed under the BSD-style license found in the\n  LICENSE file in the root directory of this source tree."
for file in $(find .. -type f -name \*.cpp | grep -v external | grep -v build); do
  echo -e "/*\n$copyright_text\n*/" > copyright-file.txt;
  echo "" >> copyright-file.txt;
  cat $file >> copyright-file.txt;
  mv copyright-file.txt $file;
done

# headers too
for file in $(find .. -type f -name \*.h | grep -v external | grep -v build); do
  echo -e "/*\n$copyright_text\n*/" > copyright-file.txt;
  echo "" >> copyright-file.txt;
  cat $file >> copyright-file.txt;
  mv copyright-file.txt $file;
done