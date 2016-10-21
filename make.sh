source /etc/tabannusi/config.sh
build()
{
if test $cpu_n = 0
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
