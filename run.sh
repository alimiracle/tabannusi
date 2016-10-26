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
cd $repository
log1=`git log -1 --pretty=%B`
log2=`cat $temp/q.txt`
log1_copy=$log1
    if [ "$log1" = "$log2" ]
then
q=1
else
echo $log1 >$temp/q.txt
remove_char="_"
log1=${log1//" "/$remove_char}
cp -R $repository $build_path/$log1
cd $build_path/$log1
/etc/tabannusi/build.sh &>$temp/$log1
echo "this build log for "$log1_copy|mutt -a $temp/$log1 -s "build log" -- $email
rm $log1
fi
