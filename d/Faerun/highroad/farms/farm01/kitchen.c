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
    add_prop(ROOM_S_MAP_FILE, "farm_e_map.txt");

    set_short("An airy kitchen");
    set_long("This large, cozy room is full of smells of good cooking. A " +
        "warm glow fills the room from the lamps hanging from the ceiling. " +
        "A large stove sits against a wall. Counters line the walls of " +
        "the kitchen. Cupboards hang above them. Windows are set in " +
        "the walls, allowing fresh air to blow in. East leads outside to " +
        "a garden.\n");

    reset_room();

    add_exit(FARM1_DIR + "great", "south");
    add_exit(FARM1_DIR + "garden02", "east");

    set_add_kitchen();
    set_add_rug("oval");
    set_extra_window("");
    set_extra_floor("It is worn in places.");
    
    num_of_windows = 2;

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
    
    ob = clone_object(FNPC_DIR + "egg_npc");
    ob->set_monster_home(FARM1_DIR + "kitchen");
    ob->move(this_object());
    
}
