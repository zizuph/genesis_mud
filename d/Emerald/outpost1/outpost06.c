/*******************************************************************************
 * Inside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/

#include "defs.h"

inherit OUTPOST_INSIDE_ROOM;
void
create_outpost_inside_room()
{
    set_short("Inside the armory");
    set_em_long("You are inside a small dark room in the outpost. " +
        "There are many racks along the walls of the room and a table in the center. " +
        "The table seems to be cluttered with metal links and assorted tools The racks " +
        "are meant to hold a variety of weapons for the soldiers. This room seems to be " +
        "the armory. The only exit from this room is back into the main hall.\n");

    add_item( ({"table" , "tables"}),
        "This table is made from heavy, sturdy wood. There are " +
        "metal links, husks of leather and some tools for repairing " +
        "armour on it.\n");

    add_item( ({"tool" , "tools"}),
        "The tools are spread out on the table, they look like pliars and " +
        "hammers, used to fix armour.\n");

    add_item( ({"links" , "metal links"}),
        "These various shapes and sizes of metal links, and rings are the " +
        "leftover pieces of repaired or resized armor.\n");

    add_item( ({"table" , "tables"}),
        "This table is made from heavy, sturdy wood. There are " +
        "metal links, husks of leather and some tools for repairing " +
        "armour on it.\n");

    add_item( ({"rack" , "racks."}),
        "These wooden racks are meant to hold the weapons of soldiers. They " +
        "look as if they are sized to hold bows, axes, swords and maces.\n");

    add_exit("outpost02.c" , "northeast");



}
