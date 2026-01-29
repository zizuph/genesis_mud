/*******************************************************************************
 * Inside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/

#include "defs.h"

inherit OUTPOST_INSIDE_ROOM;
void
create_outpost_inside_room()
{
    set_short("Inside sleeping quarters");
    set_em_long("You are inside a small sleeping area in the outpost. " +
        "There are a small number of shabby cots around this room, and " +
        "the air in here is thick and musty. The only exit from this room " +
        "is back into the main hall.\n");

    add_item( ({"cot" , "cots"}),
        "These cots are made from logs and straw. They don't look very " +
        "comfortable.\n");

    add_exit("outpost02.c" , "southwest");


}
