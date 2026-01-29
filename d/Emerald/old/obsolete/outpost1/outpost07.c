/*******************************************************************************
 * Inside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/

#include "defs.h"

inherit OUTPOST_INSIDE_ROOM;
void
create_outpost_inside_room()
{
    set_short("Inside the meeting room");
    set_em_long("You are inside a large room in the outpost.  " +
        "There are many chairs along a huge wooden table in the center of the room. " +
        "The tabletop is clear of any items, and is polished to as shine. " +
        "There is a large silvery banner hanging on the ceiling in here as well " +
        "emblazoned with the sigil of Telberin upon it's center. The chair farthest " +
        "across from you has a high back and is padded with cushions. It is your " +
        "assumption that this room is probably used to hold the meeting and " +
        "ceremonies of this outpost. The only exit from this room is back into the" +
        "main hall.\n");

    add_item( ({"table" , "tables"}),
        "This large wooden table is very clean and polished.\n");

    add_item( ({"chair" , "chairs"}),
        "Aside from the padded head chair, these chairs don't seem to look that " +
        "comfortable. They're made from rigid hard wood and look to be quite stiff.\n");

    add_item( ({"banner"}),
        "The banner that hangs from the ceiling proudly bears the sigil of Telberin " +
        "upon it's silvery cloth.\n");


    add_exit("outpost02.c" , "east");



}
