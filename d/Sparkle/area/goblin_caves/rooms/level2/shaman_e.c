/*
 * shaman area corridor base
 * Boreaulam, Mar 2014
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Middle corridor");
    set_long("This is a wide tunnel which appears to connect two large " +
        "caves. A decorative grey stone mosaic covers the floor beneath you, " +
        "twisting and turning as it follow the corridor that winds " +
        "its way through the mountain. Several torches are mounted on " +
        "the walls every so often, giving you just enough light to " +
        "see clearly. It seems that at both ends of the tunnel, the " +
        "grey stone appears to meet up with similar decorative stones " +
        "of black and white.\n\n");
    
    add_item(({"grey stones", "decorative stones", "floor", "tunnel",
    "corridor", "down", "mosaic"}),
        "There are thousands of small, decorative stones, all grey " +
        "and laid out in a river of mosaic, which cover the entire " +
        "floor of the corridor here. Following the path in " +
        "either direction will lead you out into a much larger " +
        "cave where similar decorative stones of black and white " +
        "merge with these grey stones.\n");
    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling has been roughly chiseled, " +
        "obviously worked by hand to expand what was probably a " +
        "naturally existing cave at first.\n");
    add_item(({"torch", "torches"}),
        "Several torches have been mounted on the north and south " +
        "walls here.\n");
    add_item(({"mountain", "mountains"}),
        "You are in a series of caves, far beneath the mountain above.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. This granite is very hard, but in many places " +
        "it appears that several industrious goblins have chiseled away " +
        "at the walls and ceilings to make these caves more habitable.\n");
    add_item(({"wall", "walls"}),
        "The walls here are made of the same grey stone as everything " +
        "else in these caves. Several torches have been mounted on the " +
        "walls here, providing a reasonable amount of light.\n");
    add_item(({"north wall", "northern wall"}),
        "The northern wall is rather bare, save for a handful of torches " +
        "which have been mounted here to provide some light.\n");
    add_item(({"south wall", "southern wall"}),
        "The southern wall is rather bare, save for a handful of torches " +
        "which have been mounted here to provide some light.\n");
    add_item(({"east wall", "eastern wall"}),
        "This is a tunnel, there is no eastern wall here!\n");
    add_item(({"west wall", "western wall"}),
        "This is a tunnel, there is no western wall here!\n");
    add_item(({"end", "ends"}),
        "This corridor ends into two large caves, one to the east " +
        "and one to the west.\n");
    add_item(({"east end", "eastern end"}),
        "There appears to be a rather large cave at this end of the " +
        "corridor, you will have to enter it to see more.\n");
    add_item(({"west end", "western end"}),
        "There appears to be a rather large cave at this end of the " +
        "corridor, you will have to enter it to see more.\n");

    add_exit("shaman_boss", "east", "@@check_shaman");
    add_exit("shaman_entrance", "west");
    
    add_npc(NPCS_DIR + "l2_shaman", 1, &->arm_me(0));
    
} /* create_room */

/*
 * Function name:        check_shaman
 * Description  :        you cannot pass until shaman is dead
 */
int
check_shaman()
{
    object shaman = present("_l2_shaman", this_object());
    if(shaman)
    {
        write(shaman->query_The_name(this_player()) + 
              " stops you from going any further.\n");
        return 1;
    }
    return 0;
} /* check_shaman */
