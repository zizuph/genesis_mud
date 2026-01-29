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
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("A comfortable room of a house");
    set_long("This room is where elves retire for reverie. In this room, they relax their minds and calm themselves. The simply decorated room is lit with some small candles, which are spread around the room. A few mats and some small tables are scattered around the room.\n");

    floor = "A plush carpet covers the floor.";
    
    add_item(({"rug", "carpet", "plush carpet", "plush rug"}),
        "The plush carpet is rectangular shaped. It is a deep muted " +
        "brown color, and looks comfortable to sit on.\n");
    set_elf_house();
    set_elf_mats();
    set_elf_small_tables();
    set_reverie_room();

    add_exit(GO_DIR + "house03", "east");
 
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