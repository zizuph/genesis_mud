/* 
 * Xak Tsaroth - Lower level
 * Originally coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{
    set_short("An old deserted street");
    set_long("You are at the northern end of what once must have been " +
	     "a business section. The buildings has not collapsed, " +
	     "but they lean drunkenly against those opposite, forming " +
	     "a ragged archway over the street. A small building seems " +
	     "in particulary good shape to the west.\n");

    add_exit(MIDDLE + "sidestreet2", "south");
    add_exit(MIDDLE + "flourroom", "west");

    add_item(({"building", "buildings", "small building", "wall", "walls"}),
	     "The buildings are mostly still standing but in a dangerous " +
	     "shape many of the walls are leaning over ready to " +
	     "collapse. However one small building to your west looks in " +
	     "a better state than most.\n");
}
