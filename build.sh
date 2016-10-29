#     This file is part of Tabannusi, a continuous build system.
# Copyright (c) 2016 rosa <rosa33@openmailbox.org>
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
list=`ls`
if echo "$list" | grep -q "ant.properties"; then
ant release
exit
fi
if echo "$list" | grep -q "Dockerfile"; then
docker build `pwd`
exit
fi
if echo "$list" | grep -q "Cargo.toml"; then
 cargo build
exit
fi
if echo "$list" | grep -q "autogen.sh"; then
chmod +x autogen.sh
./autogen.sh
fi
if echo "$list" | grep -q "configure"; then
chmod +x configure
./configure
fi
if echo "$list" | grep -q "Makefile"; then
/etc/tabannusi/make.sh
exit
fi
echo "I Can't Find Way to build the code"
