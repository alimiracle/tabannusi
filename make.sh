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
source /etc/tabannusi/config.sh
build()
{
if test $cpu_n = 1
then
make
else
make -j$cpu_n
fi
}
dist()
{
export DISTCC_POTENTIAL_HOSTS=$servers
pump make -j$cpu_n CC=distcc
}
if test "use_dist" = "yes"
then
dist
else
build
fi
