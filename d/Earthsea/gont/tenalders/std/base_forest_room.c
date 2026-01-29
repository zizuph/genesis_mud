/*
 * coded by Amelia 4/12/97
 * includes herbsearch and room_tell.c so that
 * they can be used if add_herb_file and add_tell
 * are used. The herb room should be inheritable
 * using create_forest_room(); in the file
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/sys/properties.h"

public void create_forest_room() { }

public nomask void
create_herb_room()
{
    set_short("Basic herb room");
    set_long("The basic room that contains herbs.\n");
    set_tell_time(120);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    add_item((({"trees", "forest", "ancient evergreen forest", "evergreen"})),
        "Tall spruce and larch trees make up this forest. Their " +
        "needles carpet the path, scenting the crisp air. " +
        "You notice that some of the trees bear marks on them " +
        "fairly high from the ground...Hmmm....\n");
    add_item("marks",
        "Examining the marks as well as you can from where you are, " +
        "you think that they look like claw or scratch marks from " +
        "some large animal!\n");
    add_item((({"needles", "pine needles"})),
        "Pine needles carpet the path and scent the air.\n");
    add_item((({"briars", "bushes"})),
        "A dense tangled undergrowth of briars and bushes " +
        "covers the rocky ground aside from the path.\n");
    add_tell("Far above in the clear air above the treetops " +
        "you see a hawk circling in a wide gyre.\n");
    create_forest_room();
}
