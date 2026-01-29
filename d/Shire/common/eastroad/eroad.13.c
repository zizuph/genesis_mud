/* File: /d/Shire/common/eastroad/eroad.13.c */ 

#define ROOM_NUMBER 13
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad east of Bree.\n"

        + "Here the Road takes a northeastern course around a marking stone. "
        + "The road continues towards a rather high mountain top, the highest of the "
        + "Weather hills north of you. This is Amon Sul (elvish for 'the Hill of Wind'). "
        + "No vegetation grows upon it, and on the top you notice that it is rather "
        + "flat, a perfect place for watching the whole area around here. "

    );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_item(({"stone"," marking stone"}),
        "The stone is a marking to show the travellers the route.\n"
    );
/*   add_exit(TEMP_DIR + "eroad.14","northeast",0); */
   add_exit(TEMP_DIR + "eroad.17","northeast",0,4);
    add_exit(TEMP_DIR + "eroad.12", "west", 0);
    add_neg("remove", "[the] [marking] 'stone'", "It is too heavy to be removed.\n");
    add_neg("move", "[the] [marking] 'stone'", "It is too heavy to be removed.\n");
    add_neg("push", "[the] [marking] 'stone'", "It is too heavy to be removed.\n");
    add_neg("pull", "[the] [marking] 'stone'", "It is too heavy to be removed.\n");
}
