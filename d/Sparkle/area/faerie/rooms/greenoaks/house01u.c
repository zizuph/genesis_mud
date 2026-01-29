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
    set_long("This is the reverie room of the house. Elves come up " +
        "here to reverie and relax, and to clear their minds of problems " +
        "and concerns. The room is large and simply decorated. A few " +
        "mats are scattered around the room for elves to sit on. Some " +
        "small tables are set next to the mats. Some small candles " +
        "are spread around the room.\n");

    floor = "A plush carpet covers the floor.";
    
    add_item(({"rug", "carpet", "plush carpet", "plush rug"}),
        "The plush carpet is rectangular shaped. It is a deep muted " +
        "brown color, and looks comfortable to sit on.\n");
    set_elf_house();
    set_add_stairs_dn();
    set_elf_mats();
    set_elf_small_tables();
    set_reverie_room();

    add_exit(GO_DIR + "house01", "down");
 
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