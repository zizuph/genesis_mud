/*
 * Kitchen of the farmhouse in Anduin
 * By Finwe, November 2005
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "local.h"
 
inherit BASE_HOUSE;

void
create_house_room()
{
    set_short("An airy kitchen");
    set_long("This large, cozy room is full of smells of good cooking. A " +
        "warm glow fills the room from the lamps hanging from the ceiling. " +
        "A large stove sits against a wall. Counters line the walls of " +
        "the kitchen. Cupboards hang above them. Windows are set in " +
        "the walls, allowing fresh air to blow in.\n");

    reset_shire_room();

    add_exit("great_room1", "south");
    set_add_kitchen();
    set_add_rug("oval");
    set_extra_window("");
    set_extra_floor("It is worn in places.");
    
    num_of_windows = 2;

}


void
reset_shire_room()
{
}
