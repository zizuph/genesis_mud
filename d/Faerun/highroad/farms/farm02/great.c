/*
 * Great room of farmhouse 
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
    set_short("A large great room");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_long("A large carpet covers the floor of this great room. Here the family gathers during the day or at night. Furniture is spread around the room and pictures hang on the walls. There is a fireplace against one wall and warms the house.\n");

    reset_room();

    add_exit(FARM2_DIR + "kitchen",  "north");
    add_exit(FARM2_DIR + "yard",     "south");

    
    set_add_great_room();
    set_add_rug("oval");
    set_add_fireplace();

}


void
reset_room()
{
    ::reset_room();
    if ((ob))
    {
        return;
    }

    ob = clone_object(FNPC_DIR + "farmer");
    ob->set_monster_home(FARM2_DIR + "great");
    ob->set_random_move(8);
    ob->set_restrain_path(FARM2_DIR);
    ob->move(this_object());

}
