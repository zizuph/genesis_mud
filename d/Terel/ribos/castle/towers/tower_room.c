/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tower_room.c
 *
 * Base room for the towers in the corners of the castle.
 *
 * Vader
 * Recoded by Sorgum 950602
 *
 * Modified by Lilith Aug 12, 2008
 * -reset changed from 90 minutes to 115 minutes
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();

    set_short("A tower");
    set_long("You are inside a large tower.  Around the edges, a " +
	     "spiral staircase leads up and down.  Light is " +
	     "provided by torches here, but you think " +
	     "you see sunlight further up.  The stones that make " +
	     "the walls here are dark and slimy.  Your footsteps " +
	     "echo loudly here.\n");

    add_item(({"torch", "torches"}), 
	     "These torches are placed high above your head, " +
	     "making it impossible to reach.  Otherwise, they are " +
	     "just your plain, ordinary torches.\n");

    add_item(({"stones", "stone", "wall"}),
	     "These stones might have once been the same color " +
	     "as those on the ooutside, but now they are covered " +
	     "in moisture and mildew, along with soot from the " +
	     "constantly burning torches.\n");

    add_item(({"sunlight"}), "You see nothing special about the sunlight.\n");

    add_item(({"staircase", "stairs", "spiral staricase", "spiral stairs"}), 
	     "A long, winding spiral staircase, constructed entirely " +
	     "of the same stones that make up the wall.  It winds " +
	     "high above your head, and continues well into the " +
	     "deep abyss.\n");

    /* ~115 minutes between reset instead of 90 */
    enable_reset(75);


    INSIDE;
}

