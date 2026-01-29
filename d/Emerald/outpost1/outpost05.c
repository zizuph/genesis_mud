/*******************************************************************************
 * Inside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/
#include "defs.h"

inherit OUTPOST_INSIDE_ROOM;
void
create_outpost_inside_room()
{
    set_short("Inside the war room");
    set_em_long("You are inside a rather messy room in the outpost. " +
        "There is a large table in the center of the room well and a few chairs too. " +
        "The table seems to be cluttered with maps and papers of all sorts The walls " +
        "have maps on them as well. This function of this room seems to be a planning " +
        "room for attacks and protection. The only exit from this room is back into " +
        "the main hall.\n");

    add_item( ({"table" , "tables"}),
        "This table is made from heavy, sturdy wood. Maps and other papers are " +
        "messily tossed along it's surface.\n");

    add_item( ({"chair" , "chairs"}),
        "These chairs don't seem to look that comfortable. They're made from rigid hard " +
        "wood and look to be quite stiff.\n");


    add_item( ({"paper" , "papers"}),
        "You pick up the nearest document and begin to read: \n " +
        "--------------------POSSIBLE QUEST?------------------.\n");

    add_exit("outpost02.c" , "northwest");



}
