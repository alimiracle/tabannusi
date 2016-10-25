Tabannusi is continuous build system, its Watching git repository , if you make new commit to the repository, the app will build the code in repository and send you the build log in your email.

"Tabannusi" is a Sumerian word that meaning "Build" in english

Requirement:
You need "gcc" to build tabannusi
and you need "mutt" to send emails

Install :
Download the program useing git:

git clone https://notabug.org/alimiracle/tabannusi

  cd tabannusi

then type  :

make
    then type "as root":

    sudo make install

to config the programme 

open the configure file as root :

     sudo nano /etc/tabannusi/config.sh

replace "yourmail"  with your email, "rp"  with your git repository, "mypath"  with your build repository path output and 1  with number of CPUS that will be used in the build

then save the file

If the code in your repository follows different build method from the standard methods

Modify "/etc/tabannusi/build.sh" file according to your need.

this build.sh file
can build this types
- app use gnu build system
- app use make
- app use rust build system
- android app
- docker image (useing Dockerfile)

To run tabannusi, type as root

    sudo tabannusi start

to restart tabannusi

type as root

sudo tabannusi restart

to stop tabannusi

type as root

sudo tabannusi stop

Distributed Build:

Distributed Build mene distribute compilation of code across several machines on a network.

tabannusi Can  do that with the help of distcc

To use  this property you need

1:

  For each machine, 

download distcc
from this link
https://codeload.github.com/distcc/distcc/tar.gz/distcc-3.1
 unpack, and do 

./configure & make & sudo make install

2:

  On each of the servers, run distccd --daemon, with --allow options to restrict access. 

3:

 open /etc/tabannusi/config.sh as root

sudo nano /etc/tabannusi/config.sh

Change use_dist value to "yes"

4:

 replace server1  with your build machines names

5:

 save the file


Price:

tabannusi free as Price
With One exception

If you met me buy me a pizza, ok??
