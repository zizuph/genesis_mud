/*
   Pax Tharkas, Ground level, Supply room in west tower.

   supply_room1.c
   --------------

   Coded ........: 95/03/02
   By ...........: Jeremiah

   Latest update : 95/03/30
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;


void
create_pax_room()
{
   set_short("Large supply room");
   set_long("You are standing in the east end of a large supply room. " +
            "Sturdy shelves line the walls only interrupted by space " +
            "for the exits. Several shelves transverse the room " +
            "obscuring the view to the rest of the supply room. \n");
	
   add_item("shelves", "Sturdy wooden shelves running along the walls " +
            "of this room. Right now they're almost all empty, except " +
            "for a few bundles of red clothings on some of the shelves " +
            "transversing the room.\n");

   add_item(({"clothing", "clothings"}), "You recognize these as the " +
            "military clothings worn by the red dragon army. They're " +
            "probably worthless to you.\n");

   INSIDE;

   add_exit(GROUND_LEVEL + "large_kitchen", "north", 0);
   add_exit(GROUND_LEVEL + "supply_room2", "west", 0);
}

