/*
 * Base room for Sparkle goblin caves
 * - Boreaulam, April 2012
 */
inherit "/std/room";

#include <stdproperties.h>
#include "defs.h"

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    set_short("Bad short description");
    set_long("Bad long description.\n\n");

    add_prop(ROOM_S_MAP_FILE, "govlin_caves_level1.txt");
    add_item("cave", "It is very large and crafted from stone. " +
                     "There are some torches to illuminate this cave.\n");
    add_item(({"walls", "stone", "stones", "wall" }),
             "The stone walls are without any decorations.\n");
    add_item(({"floor", "dirt"}), "The bare floor with some dirt.\n");
    add_item(({"torches", "torch"}),
             "Torches on the walls give enough light for this cave.\n");
    add_item(({"light", "illumination"}),
             "Light from the torches illuminates the cave.\n");
    add_item(({"room", "here"}), "Use <look> for more details.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);

} /* create_room */