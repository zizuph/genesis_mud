/*
   Pax Tharkas, Valley.....

   curtain_wall2.c
   ---------------

   Coded ........: 95/04/09
   By ...........: Jeremiah

   Latest update : 95/05/15
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;

void
create_pax_room()
{
   set_short("At the outer curtain wall");
   set_long("You are standing on a road going through an opening " +
            "in a wall running across the valley in front of Pax " +
            "Tharkas. This wall functions as an extra line of " +
            "defence in the event of an attack on the fortress. " +
            "There is a similar wall running across the valley " +
            "closer to the fortress. The gates here haven't been " +
            "maintained, and are hanging useless from their hinges. " +
            "Looking south, upwards, you see the mighty fortress " +
            "controlling the valley and the road going through it. " +
            "The road leads south, upwards, towards the fortress, " +
            "and north, into the widening valley.\n");

   OUTSIDE;

   add_item("road", "A simple dusty road running through this small " +
            "valley. The road leads through these gates and up to " +
            "to the fortress above you.\n");

   add_item("valley", "The valley is very narrow here, and ends at " +
            "fortress. There is probably a pass through the mountains " +
            "behind that fortress.\n");

   add_item(({"gate", "gates"}), "Once these must have been quite " +
            "strong gates, closing the opening in the curtain wall. " +
            "Years without maintenance has left the gates hanging " +
            "useless from their hinges.\n");	

   add_item(({"wall", "curtain wall"}), "This wall runs across the " +
            "narrow valley in front of Pax Tharkas. It adds an extra " +
            "line of defence to the fortress, and makes " +
            "the effective use of siege engines difficult.\n");

   add_item("hinges", "Large iron hinges on which the gates rest, or " +
            "rather the remains of the gates.\n");

   add_item(({"fortress", "Pax Tharkas", "Pax tharkas", "pax tharkas"}),
            "A mighty fortress looming in the pass above you. The one " +
            "who controls this fortress, controls the passage through " +
            "mountains.\n");

   add_exit(VALLEY + "valley_road1", "north", 0);
   add_exit(VALLEY + "curtain_wall1", "south", 0);
}

