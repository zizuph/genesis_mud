inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Edge of the Ringing Mountains");
  set_long("Looming to your north and west, the Ringing Mountains "
  	+"provide a formidable barrier to much continued travel.  "
  	+"A narrow path winds away northwestwards at the foot of "
  	+"the mountains, quickly become lost in all the rocky "
  	+"barrens beyond.  The desert wind howls over and through "
  	+"the gaps in the rocks nearby, providing a constant "
  	+"keening wail in your ears.  Perhaps these mountains "
  	+"were misnamed by someone, or perhaps the person didn't "
  	+"have the heart to name these mountains what they really "
	+"sound like, a wailing banshee.\n");
    add_item(({"mountains","mountain","ringing mountains"}),
	    "This massive collection of mountains rises to your "
    	+"north and west.  There are tales of the creatures who "
    	+"live in these mountains.\n");
    add_item("rocks","They lay strewn about here, obvious remnants "
    	+"of the mountains breaking before the onslaught of the "
    	+"fierce desert winds.\n");
    add_exit(DESERT + "p1","northeast");
    add_exit(DESERT + "d21","west");
    add_exit(DESERT + "d16","southwest");
    add_exit(DESERT + "d17","south");
    add_exit(DESERT + "d18","southeast");
}

