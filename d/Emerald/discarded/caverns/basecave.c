/*
 * BASECAVE.c
 * This file provides items and other common features throughout 
 * all of the cavern system beneath the island.
 * - Alaron, September 13, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit "/std/room";

void create_cave();

void
create_room()
{
    set_short("Dark cavern");
    set_long("This is a dark cavern");

    create_cave();

    add_prop(ROOM_I_INSIDE,1);

    add_prop(ROOM_S_DARK_LONG, "The cave is far too dark to make out "+
	     "any details beyond the faint images of the wet stone "+
	     "walls.\n");
    add_prop(ROOM_S_DARK_MSG, "It is far too dark in this cave to");

    add_item( ({"floor", "ground", "down", "cave floor", "cave base"}),
	     "The cold, dark stone floor of the cave is covered with "+
	     "little trails of trickling water running through the ancient "+
	     "cracks and grooves in the near-black "+
	     "rock.\n");

    add_item( ({"water", "trickles of water", "trickles", "grooves",
		"cracks", "trails", "trails of water"}),
	     "The little trails of water seem to be dripping out of the "+
             "small cracks and holes in the ceiling and running down the "+
             "side walls.\n");

    add_item( ({"walls", "wall", "sides", "side walls"}),
	     "The walls are made of dark, slime-covered rock. Moss, "+
	     "mildew and other growths have formed from the centuries "+
	     "of water running out of the ceiling and down along the "+
	     "cave walls, forming vertical channels carved out of the "+
	     "black stone.\n");

    add_item( ({"channels", "vertical channels"}),
	     "There are vertical stone channels carved out of the side "+
	     "walls. They were formed by the countless centuries of "+
	     "water dripping from the ceiling and running down the "+
	     "sides of the walls, slowly carving out patterns in the "+
	     "otherwise dark and smooth stone.\n");

    add_item( ({"ceiling", "up", "roof", "dripping water", "holes"}),
	     "The ceiling of the cave seems to be constantly dripping "+
	     "water from various places. There are hundreds of little "+
	     "holes and cracks through which water drips slowly and "+
	     "consistently. Some of the drops adhere to the rock face "+
	     "and form thin rivulets of water which run down the "+
	     "sides of the walls. These trails of water have been "+
	     "dripping for centuries, and seem to have carved several "+
	     "stone, vertical channels in the walls.\n");

    add_item( ({"cave", "surroundings", "tunnel", "cavern"}),
	     "The cavern sprawls out in a winding maze of tunnels "+
	     "and little passages, most of which are hidden by the "+
	     "shadows and darkness here. The dark walls are wet "+
	     "with dripping moisture from the ceiling and the floors "+
	     "contain little trails of running water which drips "+
	     "off of the ceiling.\n");

}



void
create_cave()
{
}
