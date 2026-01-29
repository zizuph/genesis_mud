
/*
* A starting room in the Inn of the Lost Home. Can be rented,
* or a free starting location for those in the Order of the Stars.
*
* Arman, May 2020.
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/new_village/local.h"
#include "/d/Krynn/solace/new_village/town_square/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit  SOLINROOM;

/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_solace_room()
{
    return;  
}

void
create_solace_room()
{
    set_short("Sleeping room in the Inn of The Last Home");
    set_long("You are in a sleeping room within the Inn of The Last Home. "+
        "You find this place rather cozy, with a number of snug beds "+
        "lining the strangely shaped walls that are crafted around the " +
        "upper branches of the vallenwood tree the inn has been built in. " +
        "The living tree in which the inn is built wraps its ancient branches " +
        "around it lovingly.\n");

    add_item(({"walls", "wall", "fixture", "fixtures"}), 
        "They are made out of oak wood, as is the rest of the place.\n"); 
    add_item(({"beds", "bed", "snug beds", "snug bed"}), 
        "They are comfortable looking wooden beds.\n");
    add_item(({"branches", "branch"}), 
        "The branches are huge, thick as many tree-trunks, and part of the " +
        "single, ancient vallenwood tree which support the floor and ceiling " +
        "of this structure.\n");
    add_item(({"tree", "vallenwood"}), 
        "This tree seems particularly fond of this inn, as it seems to " +
        "hold the structure in loving arms. It is huge, and quite old. " +
        "Perhaps it pre-dates the Cataclysm.\n");
    add_item(({"inn","inn of the last home"}),
        "You stand in one of the sleeping rooms of the Inn of the Last " +
        "Home, one of the largest buildings in the tree town of Solace.\n");

    add_prop(ROOM_M_NO_STEAL, "You find no opportunity to steal while in " +
        "such close confines. You may have to wait until they leave the " +
        "sleeping room.\n");
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);

    add_exit(TDIR + "inn", "down", 0);
    reset_solace_room();
}

