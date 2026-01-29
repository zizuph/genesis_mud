README Frontier LPC code generator - hobbitStartlocxxyyzz.ZIP

NOTE: This collection of scripts are in a nightmare state.
      Read on and preceed at your own responsibility and
      risk. Still they have been very useful for me.

The ZIP file in this catalog contains a project file for
Frontier 5.1.4 and will NOT work with any other version.
The project file contains scripts to generate LPC files 
from templates and database entries which are also included.

I am not sure where to get the 5.1.4 version but for the
unfrightened a newer trial version may be downloaded from
http:/www.userland.com/frontier5 somewhere but be prepared
to hack to get it to work.

To install the project file just open it from within a
fresh Frontier Root database and read it in as suggested:

websites.Halflings

Note: No other location will work!

Then install the generator menu by selecting 'Edit menu'
from the custom menu named with your initials, or whatever
you registered Frontier with, and add a menu entry with the
following script:

websites.Halflings.["#tools"].buildObject()

Also adjust the target location for the generated files
by setting websites.Halflings.rooms.#ftpSite.folder to 
whatever folder you want the files to be generated.
Currently a folder named 'room' will be created also 
within the defined folder and there all files will end 
up. From there it could be FTP:ed to Genesis.

To generate an LPC file just select the object you want to 
create and select the just installed menu choice. I.e.:

a) Highlight websites.Halflings.mobiles.spider 
b) Select the newly installed menu choice.
c) FTP the resulting file to Genesis.

I am not sure weather I will continue to do anything with
this environment but maybe a strighten things up when I 
got my hands on a newer version of Frontier. The generator
busts around with internal structures wich seems to have
changed before and after Frontier version 5.1.4.

Seaweed