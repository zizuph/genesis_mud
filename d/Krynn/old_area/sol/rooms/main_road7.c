/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

void
create_solace_room()
{
    set_place(MAINROAD);

    set_long_desc("This is the southern parts of Solace. The Solace " +
             "Main Road merges here with the road leading south " +
		  "to Haven. Looking up you can see a small house " +
		  "built among the limbs of a vallenwood, there is " +
		  "also a bridge-walk connecting the tree with other " +
		  "vallenwoods. To the northwest you can spot the Solace " +
		  "square.");

    add_exit(TDIR + "main_road6", "north");
    add_exit(TDIR + "square", "northwest");
    add_exit(C_ROAD, "south");
}


