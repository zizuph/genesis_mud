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

 static object saviro;

void
create_house_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("A clean house in Green Oaks");
    set_long("This large room is sparsely decorated. Furniture is scattered around the clean room. Warm light filters in from outdoors. A kitchen is set in one corner of the room. There is another room to the west.\n");

    set_elf_house();
    set_elf_great_rm();
    set_elf_table();
    set_elf_kitchen();
    set_add_stairs_up();

    add_exit(GO_DIR + "road18", "northeast");
    add_exit(GO_DIR + "house03a", "west");
    reset_room();
 
}

void reset_room() 
{ 
    add_stuff();
}

void
add_stuff()
{

    if(!saviro)
    {
        saviro = clone_object(NPC_DIR + "honey_npc");
        saviro->move(TO);
    }

}