/*******************************************************************************
 * Inside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/

#include "defs.h"

inherit OUTPOST_INSIDE_ROOM;
void
create_outpost_inside_room()
{
    set_short("Inside the mess hall");
    set_em_long("You are inside a small mess hall in the outpost.  " +
        "There are three large tables in here as well as quite a few chairs. " +
        "The smell of roasted meat permeates the air in here with a rather  " +
        "pleasant aroma. The only exit from this room is back into the main hall.\n");

    add_item( ({"table" , "tables"}),
        "These tables are made from heavy, sturdy wood. Food and drink stains are " +
        "visible on the tabletops along with various scratches and other markings of " +
        "everyday use.\n");

    add_item( ({"chair" , "chairs"}),
        "These chairs don't seem to look that comfortable. They're made from rigid hard " +
        "wood and look to be quite stiff.\n");

    add_exit("outpost02.c" , "west");


}
