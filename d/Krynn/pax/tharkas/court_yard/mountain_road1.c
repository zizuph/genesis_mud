/*
   Pax Tharkas, Mountain road towards the open iron ore mine.

   mountain_road1.c
   ----------------

   Coded ........: 95/03/31
   By ...........: Jeremiah

   Latest update : 95/04/12
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
   set_short("mountain road");
   set_long("You are walking on a narrow mountain road, wide enough " +
            "though, to drive a horsedrawn wagon along it. At one side " +
            "you have the mountain side rising, like an impenetrable " +
            "wall, high above you. To the other side the mountain " +
            "falls steep downwards towards to courtyard of Pax Tharkas. " +
            "Better not slip over the edge here.\n");

	
   OUTSIDE;

   add_exit(COURT_YARD + "court_yard3", "northeast", 0);
   add_exit(COURT_YARD + "mountain_road2", "southeast", "@@upwards", 3);
}


int
upwards()
{
     write("You trudge your way up the mountain road.\n");
   return 0;
}
