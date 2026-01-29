/*
  Pax Tharkas, Open iron ore mine.

  iron_mine1.c
  ------------

  Coded ........: 95/03/31
  By ...........: Jeremiah

  Latest update : 95/04/16
  By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <composite.h>

inherit PAXOUTROOM;

void
create_pax_room()
{
    set_short("Open iron ore mine");
    set_long("You are standing in an open iron ore mine. The mine has " +
        "been excavated from the mountainside, by mining away at " +
        "the rock to arrive at the precious iron ore. The excavation " +
        "has left a large scar in the mountain side. The ground is " +
        "very dusty here, and fine dust blows around with the wind. " +
        "Nobody is working in this part of the mine, but you can " +
        "hear the metallic sounds of metal against rock.\n");
	
    OUTSIDE;

    add_item("dust", "This is fine grey red dust, obvious from the " +
        "mining of rock.\n");

    add_item("ground", "The dust is whirling around in the wind, " + 
        "covering the ground with a fine layer of it.\n");

    add_item("mountain side", "The mountain side is heavily scarred " +
        "by the heavy mining done in this area.\n");

    set_tell_time(60);
    add_tell("You hear a metallic ringing sound coming from the " +
        "north.\n");

    add_exit(COURT_YARD + "iron_mine2", "north", 0);
    add_exit(COURT_YARD + "mountain_road3", "southwest", 0);
}

