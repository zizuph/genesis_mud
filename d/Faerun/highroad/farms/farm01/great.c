/*
 * Great room of farmhouse
 * By Finwe, August 2006
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

#define VAMPIRES_OBJ_DIR  "/d/Faerun/guilds/vampires/obj/"


inherit BASE_FARMHOUSE;
object ob, ob1;
void
create_house_room()
{
    add_prop(ROOM_S_MAP_FILE, "farm_e_map.txt");

    set_short("A large great room");
    set_long("This is the great room of the farmhouse. It's "
    +"large and where the family gathers during the "
    +"day. Furniture is spread around the room. A large carpet "
    +"covers the floor, and a dining room sits in one "
    +"corner of the room. A fireplace is set against "
    +"a wall and warms the house. A painting hangs above "
    +"the fireplace for additional decor.\n");

    reset_room();

    add_exit(FARM1_DIR + "kitchen",  "north");
    add_exit(FARM1_DIR + "yard",     "south");
    add_exit(FARM1_DIR + "bedroom",  "east");

    set_add_great_room();
    set_add_rug("oval");
    set_add_fireplace();
    set_extra_window("");

    num_of_windows = 5;
    
    room_add_object(VAMPIRES_OBJ_DIR  + "vamp_painting1");
}


void
reset_room()
{
    ::reset_room();

    setuid();
    seteuid(getuid());

    if ((ob))
    {
        return;
    }
     ob = clone_object(FNPC_DIR + "1farmer");
     ob->set_monster_home(FARM1_DIR + "great");
     ob->set_random_move(8);
     ob->set_restrain_path(FARM1_DIR);
     ob->move(this_object());
}
