/* File: /d/Shire/common/eastroad/eroad.15.c */ 

#define ROOM_NUMBER 15
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad east of Bree.\n"

        + "You are standing south of Amon Sul, the Weathertop. It rises a thousand feet "
        + "above you and the surrounding lowlands, probably giving a clear view of all "
        + "the terrain around it. In the east you see a different type of landscape "
        + "from the bare plains west and south of here, the Lone-lands, covered with "
	+ "heather and moss.\n"
	

    );

    add_item(({"eastroad", "road" }),
	"The road is wide, about 3 meters, and seems to be in constant use.\n");
    
      add_exit(TEMP_DIR + "eroad.16", "northeast", 0);
      add_exit(TEMP_DIR + "eroad.14", "southwest", 0);
}
