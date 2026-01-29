// file name:        /d/Avenir/common/holm/jungle/lf7.c
// creator(s):       Lilith, Nov 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do:            add code for jumping off ledge into whirlpool,
//                   resulting in death. Also, add water spirits.

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}

/* Now create the room.  */
void
create_jungle_room()
{
    set_short("in a hollow, overlooking a whirlpool");
    set_long("Grass grows thickly along the western slope of the "+
        "hollow, blending gradually into a moss-covered ledge "+
        "of rock. The ledge juts out over a deep pool, the "+
        "center of which is caught in a whirl. There are water "+
        "spirits here, and they permit no rest for the stream, "+
        "nor for those who visit it.\n");

    add_exit("lf10", "southwest", 0);
   
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_cliff();
    add_moss();
    add_atrack();
    add_stream();
    add_grass();

    add_item(({"pool", "whirl", "whirlpool"}),
        "It is cloudy and chill. Fingers of water vapour drift "+
        "in a circular motion above the torrent of water that "+
        "inexorably pulls everything beneath its surface.\n");
    add_item("ledge", "It is covered in moss and slick with "+
        "moisture.  It juts out over the pool of water with "+
        "the whirl at its center.\n");
    reset_domain_room(); 
}
