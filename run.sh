dir="/home/clara/blade"
cd $dir
log1=`git log -1 --pretty=%B`
log2=`cat /tmp/q.txt`
    if [ "$log1" = "$log2" ]
then
q=1
else
echo $log1 >/tmp/q.txt
make &>/tmp/q.tmp
echo "this build log for "$log1|mutt -a /tmp/q.tmp -s "build log" -- blade.vp2020@gmail.com
fi
