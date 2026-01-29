// file name:        /d/Avenir/common/holm/jungle/lf22.c
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
    set_short("thicket of thorn bushes");
    set_long("You are deep in a thicket of thorn bushes which has "+
        "crowded out most of the more friendly vegetation. It seems "+
        "very isolated and unnaturally quiet here. There is nothing "+
        "to do but press onward.\n");

    add_exit("lf21", "northwest", 0);
    add_exit(T_CAMP +"c1", "east", 0);

    add_item(({"thicket", "thorn bushes", "bushes"}),
        "Stubborn bushes with thick gnarled trunks and viscious "+
        "hooked thorns.\n");

    reset_domain_room();

}
