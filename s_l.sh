#     This file is part of Tabannusi, a continuous build system.
# Copyright (c) 2016 ali abdul ghani <alimiracle@riseup.net>
#     Tabannusi is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
# (at your option)    any later version.
#    Tabannusi is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#    You should have received a copy of the GNU General Public License
#    along with Tabannusi.  If not, see <http://www.gnu.org/licenses/>.
mkdir bin
mkdir bin/tmp
cp *.sh bin
cp tabannusi.c bin
cd bin
awk '{gsub("source /etc/tabannusi/config.sh", "source config.sh");print}' run.sh >file.txt
cat file.txt>run.sh
awk '{gsub("/etc/tabannusi/build.sh", "$dir/build.sh");print}' run.sh >file.txt
cat file.txt >run.sh
awk '{gsub("/etc/tabannusi/make.sh", "$dir/make.sh");print}' build.sh >file.txt
cat file.txt>build.sh
awk '{gsub("source /etc/tabannusi/config.sh", "source config.sh");print}' make.sh >file.txt
cat file.txt >make.sh
awk '{gsub("/bin/", "");print}' tabannusi.c >file.txt
cat file.txt>tabannusi.c
awk '{gsub("chdir", "// ");print}' tabannusi.c >file.txt
cat file.txt>tabannusi.c
awk '{gsub("/tmp", "tmp");print}' tabannusi.c >file.txt
cat file.txt>tabannusi.c
awk '{gsub("/var/run/", "");print}' tabannusi.c >file.txt
cat file.txt>tabannusi.c
awk '{gsub("/tmp", "`pwd`/tmp");print}' config.sh >file.txt
cat file.txt >config.sh
rm file.txt
gcc -g -Wall -o tabannusi tabannusi.c -lpthread
rm tabannusi.c
chmod +x *.*
chmod +x tabbannusi
