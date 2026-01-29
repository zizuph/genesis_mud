// file name:        /d/Avenir/common/holm/shore/shore1.c
// creator(s):       Lilith, April 97
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/shore/shore_base";

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
create_shore_room()
{
    set_short("Rocky shoreline, dead end");
    set_long("Further progress along this section of the shoreline "+
        "is blocked by a tumult of jagged, unclimbable rocks. The "+
        "beach is mostly black gravel churned by the violence "+
        "of the waves funneled between the barely emergent rocks "+
        "off-shore. There is a stiff wind blowing from the west, "+
        "carrying the scent of brackish water.\n");
    add_beachg();
    add_rocks();
    add_exit("sh2", "west", 0);

    reset_domain_room();
}

