source config.sh
cd $repository
log1=`git log -1 --pretty=%B`
log2=`cat $temp/q.txt`
    if [ "$log1" = "$log2" ]
then
q=1
else
echo $log1 >$temp/q.txt
cp -R $repository $build_path/$log1
cd $build_path/$log1
make &>/tmp/q.tmp
echo "this build log for "$log1|mutt -a /tmp/q.tmp -s "build log" -- $email
fi
