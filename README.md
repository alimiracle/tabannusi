Tabannusi is continuous build system, its Watching git repository , if you make new commit to the repository, the app will build the code in repository and send you the build log in your email.

"Tabannusi" is a Sumerian word that meaning "Build" in english

Requirement:
You need "gcc" to build tabannusi
and you need "mutt" to send emails

Install :
Download the program from this link:

https://notabug.org/alimiracle/tabannusi

then extract it ( in home folder recomended ).

  cd tabannusi

then type "as root" :

    make

    make install

to config the programme 

open the configure file as root :

     sudo nano /etc/tabannusi/config.sh

replace "yourmail"  with your email, "rp"  with your git repository and "mypath"  with your build repository path output

then save the file
If the code in your repository follows different build method from the standard methods( gnu build system or make or rust build system)
Modify "/etc/tabannusi/build.sh" file according to your need.

this build.sh file
can build this types
- app use gnu build system
- app use make
- app use rust build system

To run tabannusi, type as root

    tabannusi
Price:
tabannusi free as Price
With One exception
If you met me buy me a pizza, ok??
