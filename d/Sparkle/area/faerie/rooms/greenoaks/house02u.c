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
    set_short("An upstairs room of a house");
    set_long("Warm, candles flicker in the room. They are white colored and fill the room with the smell of honey. The room is relaxing and where elves spend time clearing their minds and unwinding. Some mats and small tables are spread around the room.\n");

    floor = "A plush carpet covers the floor.";
    
    add_item(({"rug", "carpet", "plush carpet", "plush rug"}),
        "The plush carpet is rectangular shaped. It is a deep muted " +
        "brown color, and looks comfortable to sit on.\n");
    set_elf_house();
    set_add_stairs_dn();
    set_elf_mats();
    set_elf_small_tables();
    set_reverie_room();

    add_exit(GO_DIR + "house02", "down");
 
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