/*
   Pax Tharkas, Valley.....

   valley_road5.c
   --------------

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
   set_short("Road in valley");
   set_long("You are standing on a road in a valley. The mountains " +
            "bordering the valley, are lower here than to the " +
            "southwest, and they become even lower further towards " +
            "northeast. The distance to the bordering mountains " +
            "enlarges towards the northeast. The road leads south" +
            "west deeper into the valley, and northeast, out of the " +
            "valley.\n");
	
   add_item("road", "A simple dusty road, running through a small " +
            "valley.\n");

   add_item(({"mountain", "mountains"}), "The Kharolis mountains " +
            "going from east to west across the southern Abanasinia, " +
            "as a natural barrier, blocking free movement southwards. " +
            "Travellers has to pass through these mountains to reach " +
            "the lands south of Abanasinia.\n");

   add_item("valley", "You are standing in it. A small valley cutting " +
            "into the mountains, leading to .. Well, who knows ?\n"); 

   OUTSIDE;

   add_exit(VALLEY + "valley_road6", "northeast", 0, 2);
   add_exit(VALLEY + "valley_road4", "southwest", 0, 2);
}
