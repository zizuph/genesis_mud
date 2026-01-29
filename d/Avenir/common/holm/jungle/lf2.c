// file name:        /d/Avenir/common/holm/jungle/lf2.c
// creator(s):       Lilith, Nov 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

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
    set_short("Fork in the trail");
    set_long("There is a fork in the trail here. Tree limbs "+
        "intertwine above, forming a green cathedral canopy of "+
        "breathtaking beauty. Mosses beard the trunks of trees "+
        "and vines dangle from limbs like locks of hair. "+
        "You can just see the dark waters of the Sybarus Sea "+
        "from where you stand, as the undergrowth has thinned "+
        "considerably. The constant, gentle slapping of water "+
        "against the shoreline is a balm to your mind."+     
        "\n");

    add_exit("lf3", "east", 0);
    add_exit("lf1", "west", 0);
    add_exit("lf6", "southwest", 0);

    add_cliff();
    add_seawall();
    add_fern();
    add_moss();
    add_atrack();

    add_item(({"west", "west trail", "west path"}),
       "This path leads west, ending at the northwest shore of the "+
       "island. "+
       ".\n");  
    reset_domain_room();
}
