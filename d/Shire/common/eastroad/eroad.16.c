/* File: /d/Shire/common/eastroad/eroad.16.c */ 

#define ROOM_NUMBER 16
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad going east of Bree. To the "+
	  "north you can see Amon Sul, or Weathertop, rising thousands "+
	  "of feet above you. Standing at its apex would probably "+
    "provide you with a clear view of the surrounding area. "+
	  "To the east there is a different kind of landscape, different from "+
	  "the plains towards the west, and the Lone-lands to the south.\n");
    add_item(({"eastroad", "road" }),
	"The road is sandy, about 3 meters wide, and seems to be in constant use.\n"
    );
    add_item(({"sand"}),
    "The sand seems to be dry. Hmm...you wonder where it came from.\n");


    add_exit(TEMP_DIR + "eroad.17", "northeast", 0);
    add_exit(TEMP_DIR + "eroad.15", "southwest", 0);
}
