// file name:        /d/Avenir/common/holm/jungle/lf21.c
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
    set_short("jungle bordered by a thicket");
    set_long("You stand in an area where the jungle plants are being "+
        "out-competed by a thicket of thorn bushes. North, however, "+
        "lowland forest grows unimpeded, teeming with life. West, the "+
        "sound of waves crashing "+
        "against the shoreline can be clearly heard. The barest hint of "+
        "a strange smell comes from beyond the thorn bushes east of you.\n");

    add_exit("lf20", "west", 0);
    add_exit("lf22", "southeast", 0);

    add_item(({"thicket", "thorn bushes", "bushes"}),
        "Stubborn bushes with thick gnarled trunks and viscious "+
        "hooked thorns.\n");

    add_cliff();
    add_atrack();

    reset_domain_room();
}


  