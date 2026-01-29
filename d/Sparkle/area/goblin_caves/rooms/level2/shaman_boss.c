/*
 * shaman area boss room
 * Boreaulam, Apr 2014
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

    set_short("Large room");
    set_long("You are standing in a rather large cave, where an intricate " +
        "mosaic spreads out across the floor. In the middle of the mosaic, " +
        "there is a solid, stone altar which rises up in an almost " +
        "threatening and ominous fashion. There are three tunnels " +
        "which lead away from this room to the west, each following a " +
        "trail of decorative stones which branch out from the mosaic " +
        "at your feet. The walls and ceiling here are carved from the " +
        "dull, grey stone of the mountain, all brightly illuminated by " +
        "the torches which have been hung upon the walls here.\n\n");

    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling has been roughly chiseled, " +
        "obviously worked by hand to expand what was probably a " +
        "naturally existing cave at first.\n");
    add_item(({"torch", "torches"}),
        "Several torches have been mounted on the north, east and south " +
        "walls here.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. This granite is very hard, but in many places " +
        "it appears that several industrious goblins have chiseled away " +
        "at the walls and ceilings to make these caves more habitable.\n");
    add_item(({"wall", "walls"}),
        "The walls here are made of the same grey stone as everything " +
        "else in these caves. Several torches have been mounted on the " +
        "walls here, providing a reasonable amount of light.\n");
    add_item(({"altar", "stone altar", "solid altar", "solid stone altar"}),
        "This altar has been carved out of a solid black stone, the surface " +
        "taking on a smooth, almost polished, appearance.\n");  
    add_item(({"floor", "down"}),
        "The floor here is covered in a strange mosaic of decorative stones. " +
        "There are three colours of stones: black, white and grey, with " +
        "each colour flowing away from the mosaic to lead down its own " +
        "path along one of the western tunnels.\n"); 
    add_item(({"east wall", "eastern wall"}),
        "The eastern wall is rather bare, save for a handful of torches " +
        "which have been mounted here to provide some light.\n"); 
    add_item(({"north wall", "northern wall"}),
        "The northern wall is rather bare, save for a handful of torches " +
        "which have been mounted here to provide some light.\n");
    add_item(({"south wall", "southern wall"}),
        "The southern wall is rather bare, save for a handful of torches " +
        "which have been mounted here to provide some light.\n");
    add_item(({"west wall", "western wall"}),
        "There are three corridors tunneling away from this cave in the " +
        "western wall. Each of the corridors has a path of decorative " +
        "stones which cover the floor.\n");
    add_item(({"west tunnel", "west corridor", "western tunnel",
            "western corridor"}),
        "The western corridor follows a path of decorative grey stones, " +
        "flowing out of the mosaic at your feet and trailing off down " +
        "the tunnel.\n");
    add_item(({"northwest tunnel", "northwest corridor", "northwestern tunnel",
            "northwestern corridor"}),
        "The northwestern corridor follows a path of decorative white " +
        "stones, flowing out of the mosaic at your feet and trailing off " +
        "down the tunnel.\n");
    add_item(({"southwest tunnel", "southwest corridor", "southwestern tunnel", 
            "southwestern corridor"}),
        "The southwestern corridor follows a path of decorative black " +
        "stones, flowing out of the mosaic at your feet and trailing off " +
        "down the tunnel.\n");
    add_item(({"mosaic", "strange mosaic", "floor"}),
        "There is a rather strange and mysterious looking mosaic which " +
        "covers the floor of this large cave. There are decorative stones " +
        "of white, grey and black merged into a circle which surrounds a " +
        "black stone altar before spreading out into the tunnels. Each of " +
        "the three colours of stones follows its own corridor, white to the " +
        "northwest, grey directly to the west and lastly black to the " +
        "southwest.\n");
    add_item(({"corridor", "corridors", "tunnels", "tunnel"}),
        "There are three corridors which lead west out of this cave, " +
        "each with a path of decorative stones covering the ground.\n");
    add_item(({"trails", "trail", "stones", "decorative stones",
            "decorative stone"}),
        "There are three trails of decorative stones on the floor here, " +
        "each leading into one of the three corridors leading away from " +
        "this cave.\n");

    add_exit("shaman_se", "southwest");
    add_exit("shaman_e", "west");
    add_exit("shaman_ne", "northwest");
    
    add_npc(NPCS_DIR + "l2_shaman_boss", 1, &->arm_me(1));
    
} /* create_room */

