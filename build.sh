list=`ls`
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
make
