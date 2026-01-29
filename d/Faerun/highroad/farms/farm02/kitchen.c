/*
 * Farmhouse kitchen
 * By Finwe, August 2006
 */
 
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
 
inherit BASE_FARMHOUSE;

object ob;

void
create_house_room()
{
    set_short("A cozy kitchen");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_long("This is a large, cozy kitchen. The smell of fresh bread and " +
        "pie waft through the room. Wooden counters line the walls and " +
        "large cupboards hang above them. Windows let in warm light. " +
        "A warm glow fills the room from lamps hanging from the ceiling. A " +
        "door leads north out to a garden.\n");

    reset_room();

    set_add_kitchen();
    set_add_rug("oval");
    set_extra_window("");
    set_extra_floor("It is worn in places.");  

    add_exit(FARM2_DIR + "garden01", "north");
    add_exit(FARM2_DIR + "bedroom", "west");
    add_exit(FARM2_DIR + "great", "south");
}


void
reset_room()
{
    ::reset_room();

    if ((ob))
    {
        return;
    }

    ob = clone_object(FNPC_DIR + "woman");
    ob->set_monster_home(FARM2_DIR + "kitchen");
    ob->set_random_move(8);
    ob->set_restrain_path(FARM2_DIR);
    ob->move(this_object());
}
