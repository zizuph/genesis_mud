/*
 * Equipment room of the Noldor Guild
 * By Finwe, January 2020
 */

#pragma strict_types

#include "noldor.h"
#include "/d/Shire/rivendell/local.h"

inherit BUILDING_BASE;

void
create_guild_room()
{
    set_short("A storage room");
    set_long("This is the storage room of the Noldor. They store equipment " +
        "for their travels here to be shared with others who travel " +
        "outside the Valley. " +
        "Lamps and @@daylight_desc@@ flowing in from the windows " +
        "fills the room with light. A large rack is set against one wall. \n");

    set_extra_wall("Large windows are set into the south and " +
        "west walls, filling the room with @@daylight_desc@@.\n");

    set_extra_window("The windows are set into the south " +
	    "and west walls.");
    add_item(({"west window", "western window"}),
         "A winding path leads southwest towards the house.\n");

    room_add_object(NOLGLD_DIR + "obj/rack");

    add_exit(NOLGLD_DIR + "rest_rm", "south");

}

void
init()
{
    ::init();
}
