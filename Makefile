all: f.c
	gcc -g -Wall -o f f.c
clean: 
	$(RM) f
install:
	mkdir /etc/f
	cp f /bin
	cp run.sh /bin
	cp config.sh /etc/f
	cp build.sh /etc/f
	chmod +x /etc/f/config.sh
	chmod +x /etc/f/build.sh
	chmod +x /bin/f
	chmod +x /bin/run.sh
.ONESHELL: