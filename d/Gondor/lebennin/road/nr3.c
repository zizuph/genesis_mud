/*
 *	/d/Gondor/lebennin/road/nr3.c
 *
 *	This version:
 *	Copyright (c) 1997 by Christian Markus
 *
 *	Modification log:
 *	 2-Feb-1997, Olorin:	General revision,
 *				changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/lebennin/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_road()
{
    set_area("northeast");
    set_areadesc("field");
    set_grass("light green");

    add_exit(LEB_DIR + "road/nr2",       "northeast", 0, 3);
    add_exit(LEB_DIR + "road/nr4",       "south",     0, 3);
    add_exit(THORN_DIR + "r7", "west",      0, 2);

    set_extraline("The road makes a slight bend here: northeast it " +
        "leads to the Harlond just outside Minas Tirith and southwest " +
        "it runs over the plains of Lebennin to finally come to " +
        "Pelargir upon Anduin in the south. A smaller road leads " +
        "away from the main road to the west.");
    add_item( ({ "small road", "smaller road", }), BSN(
	"The smaller road leads away from the main road. It is not as " +
        "wide and little more than a dirt track."));
    add_item( ({ "bend", "curve", }), BSN(
        "The road runs around a small hill keeping the road as level " +
        "as possible to make travel on the road easier."));

    add_rammas();
    add_road(1, "The roads makes a bend here, turning from northeast " +
	     "to west to run around a small hill.");
    add_ground();
    add_white_mountains("north");
    add_harlond();
    add_anduin("north");
    add_item( ({ "hill", "small hill", "meadows", }), BSN(
        "The small hill is rising gently on the inside of the bend " +
	"that the road makes to run around it. The hill is covered " +
        "with grass and on top of it stands a small group of trees."));
}
