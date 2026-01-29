/*
 * Elf house in Green Oaks
 * By Finwe, April 2005
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit HOUSE_BASE;

void add_stuff();
 
void
create_house_room()
{
    set_short("A nice house in Green Oaks");
    set_long("This is a nice house in Green Oaks. It is the house of an " +
        "elf and is decorated with a few pieces of furniture. The walls " +
        "are a soft, brown color, and resemble forest of trees. In " +
        "one corner you see a counter and a pantry where meals are " +
        "prepared. A staircase leads upstairs.\n");

    set_elf_house();
    set_elf_great_rm();
    set_elf_table();
    set_elf_kitchen();
    set_add_stairs_up();

    add_exit(GO_DIR + "road10", "east");
    add_exit(GO_DIR + "house02u", "up");
 
}

void reset_room() 
{ 
    //add_stuff();
}

void
add_stuff()
{
    object testelf;

//    if(!present("testelf"))
    {
//        testelf = clone_object(NPC_DIR + "test_elf");
        testelf->move(TO);
    }

}