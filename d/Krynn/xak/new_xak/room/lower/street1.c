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
    set_short("On the Great Plaza street");
    set_long("You are standing at the east end of the Great Plaza street. " +
	     "To the north is an entrance to a building that seems ready " +
	     "to collapse any minute. A cascade of water comes from the " +
	     "precipice above you forming the East Falls. The water " +
	     "later forms a stream that divdes the street in two halves. " +
	     "The street continues to the west along the stream.\n");

    add_item(({"water", "waterfall", "east falls"}), "The water is from " +
	     "Newsea. And thinking on how deep down you are, then you " +
	     "must have Newsea above you.\n");
    add_item("building", "It seems ready to collapse, but it has stand " +
	     "all the time since the Cataclysm, so it will probably " +
	     "stand a while longer.\n");

    add_exit(LOWER + "winebottom", "north");
    add_exit(LOWER + "street2", "west");
}



