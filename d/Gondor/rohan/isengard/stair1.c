/*
 *  /d/Gondor/rohan/isengard/stair1.c
 *
 *  Opus, April 1997
 *
 *  Copyright   1997 by Robert Miller
 *
 *  Modification log:
 */

#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;

#include <macros.h>
#include <stdproperties.h>

//Prototypes
string  getmold();

public void
create_isengard()
{
    set_short("stairway from storeroom to lookout");
    set_long(BSN(
	"This in the middle of a winding staircase which "+
	"allows passage between the upper and lower levels of the "+
	"entrance tunnel. Upward, an opening leads onto a lookout, "+
	"while going down will lead into a darkened room."));

    add_item( ({"stair", "stairs", "staircase", "winding staircase"}), BSN(
	"The stairs have been carved from the massive rock that makes up "+ 
	"the entire area. Just wide enough for two people, it winds its "+
	"way upward through the ceiling or down to a darkened room below.")); 
    add_item( ({"rock", "massive rock", "black rock",
	"massive black rock"}), BSN(
	    "This strange black rock makes up this entire area. "+
	    "It has been carved and shaped to form this "+
	    "staircase within the ringwall."));
    add_item( ({"floor", "ground", "room", "storage room"}), BSN(
	"At the foot of the stairs the floor of a dark room stretches "+
	"beyond sight."));
    add_item( ({"tunnel", "entrance tunnel", "ringwall tunnel"}), BSN(  
	"The tunnel is not visable from here, but these stairs lead "+
	"somewhere just above it."));
    add_item( ({"isengard", "fortress"}), BSN(
	"The fortress Isengard is not visable from inside thie ringwall."));
    add_item( ({"opening", "lookout"}), BSN(
	"At the top of the staircase, this opening allows someone to step "+
	"through, onto the lookout that has been constructed upon the top "+
	"of the ringwall."));
    add_item( ({"ring", "ringwall"}), BSN(
	"The black rock making up the ringwall surrounds this stairway."));
    add_item( "ceiling", BSN(
       "High above, the ceiling of the room is perfectly "+
       "rounded making it difficult to tell where the ceiling ends and "+
       "the wall begins."));
    add_cmd_item( "wall", ({"touch", "feel"}), BSN(
       "The walls are very damp to the touch and have bits "+
       "of mold growing in various spots on them."));
    add_cmd_item( "mold", ({"touch", "feel"}), BSN(
        "The mold feels slimy and a bit sticky."));
    add_cmd_item( "mold", ({"get", "take"}), getmold());

    add_exit(ISEN_DIR + "lookout2.c", "up", 0, 3); 
    add_exit(ISEN_DIR + "storerm1.c", "down", 0, 1);  
    add_prop(ROOM_I_INSIDE, 1);

}
string
getmold()
{
   // will be used in the near future so that a player can actually
   // get the mold from the walls.

}



