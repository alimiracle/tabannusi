all: tabannusi.c
	gcc -g -Wall -o tabannusi tabannusi.c -lpthread
clean: 
	$(RM) tabannusi
install:
	mkdir /etc/tabannusi
	cp tabannusi /bin
	cp run.sh /bin
	cp config.sh /etc/tabannusi
	cp build.sh /etc/tabannusi
	chmod +x /etc/tabannusi/config.sh
	chmod +x /etc/tabannusi/build.sh
	chmod +x /bin/tabannusi
	chmod +x /bin/run.sh
.ONESHELL: