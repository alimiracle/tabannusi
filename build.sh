list=`ls`
if echo "$list" | grep -q "configure"; then
chmod +x configure
fi
make
