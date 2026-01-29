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
    set_short("A clean house in Green Oaks");
    set_long("This is a great room of the house. It is neat and clean, " +
        "and large by elf standards. The house is built to resemble a " +
        "forest glade. The room is sparsely decorated with a few pieces " +
        "of furniture. In one corner is a kitchen and a staircase leading " +
        "upstairs.\n");

    set_elf_house();
    set_elf_great_rm();
    set_elf_table();
    set_elf_kitchen();
    set_add_stairs_up();

    add_exit(GO_DIR + "road10", "east");
    add_exit(GO_DIR + "house01u", "up");
 
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