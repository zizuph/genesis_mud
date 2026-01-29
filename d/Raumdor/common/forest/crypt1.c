#include "defs.h"
inherit CRYPT_ROOM;

/* SARR */

object ob;
object door;

void
create_room()
{
    ::create_room();
    set_long("You are now in a small lair behind the rushing waterfall. "+
    "The light here is dim, and the cave floors and walls are very "+
    "slippery. On the far south side of the lair, you see a very "+
    "large door.\n");
    add_item("waterfall","It cascades down the hill into the stream "+
    "that runs through the forest. Where it ends, who knows. Only one "+
    "way to find out.\n");
    add_item(({"walls","floors"}),"They are very wet and slick.\n");
    door = clone_object(FOREST_DIR + "c_door1");
    door->move(TO);
    add_exit(FOREST_DIR + "wforest42","out");
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(FOREST_DIR + "s_guard");
        ob->move_living("xxx",TO);
    }
}

