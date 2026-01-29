/*
 *	/d/Gondor/lebennin/road/nr6.c
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
    set_areadesc("bridge");
    set_grass("light green");

    add_exit(LEB_DIR + "road/nr5",     "northeast", 0, 3);
    add_exit(LEB_DIR + "road/nr7",     "southwest", 0, 3);
    add_exit(LEB_DIR + "road/wqroad1", "northwest", 0, 3);
   
    set_extraline("The road leads northeast and southwest, " +
        "crossing the river Erui here on a stone bridge. A " +
	"smaller road branches off just north of the bridge, " +
	"leading northwest towards the mountains.");
    add_rammas();
    add_road(1, "The road runs northeast to Minas Tirith and southwest " +
	"across the plains of Lebennin towards Pelargir upon Anduin " +
        "in the south. It crosses the river Erui on a stone bridge " +
        "here.");
    add_item( ({ "small road", "smaller road", }), BSN(
	"The road leads towards the northwest over green fields " +
        "and meadows on the northern bank of the Erui. It seems " +
        "to lead towards the White Mountains."));
    add_ground("the ground is brown and wet on which nothing");
    add_white_mountains("north");
    add_item( ({ "bridge", }), BSN(
        "It is a large bridge with two wide arches resting on a " +
        "thin stone pier in the middle of the river Erui."));
    add_item( ({ "river", "erui", }), BSN(
        "The Erui is a clear blue stream, flowing southeast " +
        "into the Great River Anduin. You see fish darting " +
        "around in the water."));
    add_item("fish",
        "These tiny fish dart about in the water in search of food.\n");
    add_item("water", "The water is clear and cold.\n");
}

