/*
 * Connection to the rest of Genesis 
 */

#include "../defs.h"

inherit AVENIR_SEA +"avenir_sea-x";

void
create_sea_room ()
{
    ::create_sea_room();
    add_row_exits(SPARKLE_LINK, "west", 0, 1);

    reset_sea_room();

    add_item("west", "West lies the rough waters of the Toroid High Seas.\n");

}
