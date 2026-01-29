/*******************************************************************************
 * Inside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/


#include "defs.h"

inherit OUTPOST_INSIDE_ROOM;
void
create_outpost_inside_room()
{
    set_short("The captains chamber");
    set_em_long("You are inside a large octagonal room in the building " +
        "that you saw from the gates. There is a large glass covered hole " +
        "in the ceiling, that lets natural light in. " +
        "There is also a large oaken desk on the far side of the room, and many chairs " +
        "line the octagonal sides of this room. Behind the desk, there is a large " +
        "high-backed, padded oak chair. On either side of the desk there is a flag " +
        "bearing the sigil of Telberin. The air in here is rather smoky from the " +
        "torches that are chained to the walls. There is a small staircase leading " +
        "down into the main hall below in the center of this room.\n");

    add_item( ({"glass" , "light" , "ceiling"}),
        "The hole in the ceiling is not very big, and is covered with glass, to act " +
        "as a source for natual light.\n");

    add_item( ({"flag" , "flags"}),
        "The flags are city flag of Telberin.\n");

    add_item( ({"desk"}),
        "The desk is made of fine oak, it has tooled woodwork all over it, depicting " +
        "forest settings and animal wildlife.\n");

    add_item( ({"chairs"}),
        "These chairs don't seem to look that comfortable. They're made from rigid hard " +
        "wood and look to be quite stiff.\n");

    add_item( ({"chair" , "padded chair" , "high-backed chair"}),
        "The chair behind the desk is large and comfortable looking. It's high back, "+
        "plush padded seat, and fancy woodwork makes it seem out of place here.\n");

    add_exit("outpost02.c" , "down");



}
