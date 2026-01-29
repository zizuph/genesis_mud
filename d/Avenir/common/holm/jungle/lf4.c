// file name:        /d/Avenir/common/holm/jungle/lf4.c
// creator(s):       Lilith, Oct 96
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
    set_short("Following a narrow trail");
    set_long("Shrubs spring up alongside a narrow trail of churned-up "+
        "dirt, their slender branches like little fingers plucking at "+
        "you as you brush past. All around is a forest of mossy limbs,"+
        " every tree branch draped with moss like green wool hung out "+
        "to dry. The fronds of tree ferns tremble deli"+
        "cately in the steady stream of air carrying the scent of the "+
        "Sybarus Sea from the west."+ 
        "\n");

    add_exit("lf5", "east", 0);
    add_exit("lf3", "west", 0);

    add_treefern();
    add_item(({"west", "west trail", "west path"}),
       "This path leads west, toward the shore of the island. The "+
       "vegetation in this direction is thinner than to the east "+
       ".\n");  

    add_cliff();
    add_seawall();
    add_fern();
    add_moss();
    add_atrack();
    reset_domain_room();
}
