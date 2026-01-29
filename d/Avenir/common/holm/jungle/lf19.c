// file name:        /d/Avenir/common/holm/jungle/lf19.c
// creator(s):       Lilith, Nov 97
// revisions:
// purpose:
// note:
// bug(s):
// to-do

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
    set_short("thicket south of the jungle");
    set_long("You stand in a thicket of thorn bushes, on a slight "+
        "mound that slopes upward in the southeast. North, the lowland "+
        "jungle glows a hundred shades of green, teeming with life. "+
        "A thin mist rises from the ground, trailing wraith-like "+
        "around your ankles. A dark spire dominates the skyline.\n");

    add_exit("lf20", "southwest", 0);
    add_exit("lf18", "north", "@@tear_me");

    add_item(({"thicket", "thorn bushes", "bushes"}),
        "Stubborn bushes with thick gnarled trunks and viscious "+
        "hooked thorns.\n");

    add_cliff();
    add_moss();
    add_atrack();
    reset_domain_room();
}

int 
tear_me()
{
    write("\nOuch! A thorn pricks you as you push north.\n");
    return 0;
}
  