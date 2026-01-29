/*
   Pax Tharkas, Mountain road towards the open iron ore mine.

   mountain_road3.c
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

#define THARKADAN_ENTRY    "/d/Krynn/tharkadan/room/path1"

void
create_pax_room()
{
   set_short("mountain road");
   set_long("You are walking on a narrow mountain road, wide enough " +
            "though, to drive a horsedrawn wagon along it. At one side " +
            "you have the mountain side rising high above you. To the " +
            "other side the mountain falls steep downwards towards to " +
            "courtyard of Pax Tharkas. The road splits into a fork " +
            "here. One road leading, northeast, into a dusty open " +
            "iron ore mine, one leading further up, along a narrow " +
            "pass, into the mountains, and one leading downwards, to " +
            "the fortress of Pax Tharkas.\n");
   OUTSIDE;

   add_exit(COURT_YARD + "mountain_road2", "west", 0);
   add_exit(COURT_YARD + "iron_mine1", "northeast", 0);
   add_exit(THARKADAN_ENTRY, "southeast", "@@upwards"); 
}


int
upwards()
{
   write("You trudge your way up the mountain road.\n");
   return 0;
}


int
construction()
{
   write("The path to the dwarven realm of Thorbardin is currently " +
         "closed, by order of Lord Verminaard.\n");
   return 1;
}
