/*
 * A beach in Roke by Ckrik, 9/2003
 */
#include "defs.h"

inherit ROKE_BEACH + "std/base_beach_rocky.c";
 
void
create_beach()
{
    add_my_desc("You see the town of Thwil far to the south.\n");
    add_item("town",
	     "An unnatural aura seems to emanate from the perimeter of " +
	     "the town.\n");
 
    add_exit(ROKE_BEACH+"rooms/beach05","east");
    add_exit(ROKE_BEACH+"rooms/beach03","southwest");
}
