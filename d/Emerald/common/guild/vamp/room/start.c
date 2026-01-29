/* start.c created by Shiva@Genesis.
 * This is the vampire guild's start room
 */

#pragma save_binary

#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";
inherit VAMP_LIB_DIR + "lair";

void
create_vamp_room()
{
    set_short("Temple Crypt");
    set_long("   You find yourself in a large, underground crypt. " +
	"Dozens of coffins, most of which are open and empty, " +
	"line the walls, which seem to emit a strange, dark " +
	"aura.\n");
  
    add_prop("_room_s_light_desc", "It's extremely dark in here!\n");
  
    add_exit("hall1", "up");
}

/*
 * Not good to not load.

public varargs mixed
long(string str, object for_obj)
{
    mixed cl;
    if (!(cl = coffin_long(str, for_obj)))
    {
        return ::long();
    }

    return cl;
}

public int
item_id(string str)
{
    return (coffin_id(str) ? 1 : ::item_id(str));
}

*/

public void
init()
{
    ::init();
    init_lair();
}
