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
    set_short("An airy kitchen");
    set_long("This large, cozy room is full of smells of good cooking. A " +
        "warm glow fills the room from the lamps hanging from the ceiling. " +
        "A large stove sits against a wall. Counters line the walls of " +
        "the kitchen. Cupboards hang above them. Windows are set in " +
        "the walls, allowing fresh air to blow in.\n");

    reset_room();

    add_exit(FROOM_DIR + "1great", "south");
    set_add_kitchen();
    set_add_rug("oval");
    set_extra_window("");
    set_extra_floor("It is worn in places.");
    
    num_of_windows = 2;

}


void
reset_room()
{
    setuid(); 
    seteuid(getuid());
    
    if (!objectp(ob))
    {
        ob = clone_object(FNPC_DIR + "egg_npc");
        ob->set_monster_home(FROOM_DIR + "1kitchen");
        ob->move(this_object());
    }
}
