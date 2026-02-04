/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * top_tower_room.c
 *
 * Base room for the towers in the top level corners of the castle.
 *
 * Vader
 * Recoded by Sorgum 950712
 *
 * Modified by Lilith Aug 12, 2008
 * -reset changed from 90 minutes to 115 minutes
 *
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
    set_long("You are inside a large tower.  Around the edges, a spiral " +
	     "staircase  leads down.  Light shines through the " +
	     "doorways here.  The stones that make the walls here are " +
	     "dark and slimy.  Your footsteps echo loudly here.\n");
 
    add_item(({"stones", "stone", "wall"}), 
	     "These stones might have once been the same color as " +
	     "those on the outside, but now they are covered in " +
	     "moisture and mildew, along with soot from the " +
	     "constantly burning torches.\n");
 
    add_item(({"sunlight"}), "You see nothing special about the sunlight.\n");
 
    add_item(({"staircase", "stairs", "spiral staricase", "spiral stairs"}), 
	     "A long, winding spiral staircase, constructed entirely " +
	     "of the same stones that make up the wall.  It winds down, " +
	     "deep into the abyss.\n");
    /* ~115 minutes between reset instead of 90 */
    enable_reset(75);


    INSIDE;
}

