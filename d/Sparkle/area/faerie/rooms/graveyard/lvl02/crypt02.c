/*
 * The graveyard of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/room"; 
inherit GRAVEYARD_BASE;
 
void
create_graveyard_room()
{
    set_short("Under the dark crypt");
    set_long("The crypt is dark and cold. A feeling of unrest permeates " +
        "the area and broken coffins litter the room. A shaft of dark " +
        "light shines down along the staircase, providing only limited " +
        "light. There is a hole in the wall leading north.\n");

    add_prop(ROOM_I_LIGHT, 1); // light
    set_underground();

    add_item(({"walls"}),
        "The walls are circular and constructed of gray stones. They " +
        "are bare of any decoration. A staircase is set against one wall " +
        "and leads upstairs.\n");
    add_item(({"ground", "floor"}),
        "The ground is made of gray stones. They are smooth but some " +
        "have cracks in them.\n");
    add_item(({"ceiling"}),
        "The ceiling is round, like the rest of the room. It is flat " +
        "and unadorned. There is a round staircase that descends from " +
        "above, and follows the walls.\n");
    add_item(({"staircase", "stairs", "round staircase", "round stairs"}),
        "The staircase is made of stone and is wide. It rises from the " +
        "back of the crypt, along the wall and up to an opening in " +
        "the ceiling.\n");
    add_item(({"opening"}),
        "This is a round hole in the ceiling for the staircase.\n");
    add_item(({"shaft of light"}),
        "This is a ghostly light from the crypt above. It comes from " +
        "the opening in the ceiling and gives a little light to the room.\n");
    add_item(({"hole", "hole in the wall"}),
        "Something with great strength made this hole. Broken stones and " +
        "dirt lay around the edge of the hole, as if it was punched in " +
        "from the other side. It leads into darkness.\n");
    add_item(({"broken stones"}),
        "These are from the hole in the wall, and were shattered by " +
        "an incredible force. They are no longer smooth but cracked " +
        "and broken.\n");

    add_exit(GRAVE2_DIR + "gr2_02", "north");
    add_exit(GRAVE2_DIR + "gr2_04", "east");
    add_exit(GRAVE1_DIR + "crypt01_in", "up");

    reset_room();
}

void
reset_room()
{

}