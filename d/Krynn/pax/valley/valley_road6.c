/*
   Pax Tharkas, Valley.....

   valley_road6.c
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
   set_short("Valley entrance");
   set_long("You are standing on a road at the mouth of a wide valley. " +
            "The flat plains north of you slowly rises into low hills " +
            "ending up as low mountain ridges bordering the wide valley " +
            "south of you. Beyond the valley, and to each side of the " +
            "valley mouth, you see the Kharolis mountains reaching " +
            "majestically towards the sky.\n");
	
   add_item("road", "A simple dusty road, running into a small " +
            "valley.\n");

   add_item(({"mountain", "mountains"}), "The Kharolis mountains " +
            "going from east to west across the southern Abanasinia, " +
            "as a natural barrier, blocking any movement southwards. " +
            "Travellers has to somehow pass over, or through, these " +
            "mountains to reach the lands south of Abanasinia.\n");

   add_item("valley", "You are standing at the mouth of a valley " +
            "leading southwards into the mountains. Maybe there is " +
            "a way to cross, or pass through, the mountains in there.\n");

   add_item(({"hill", "hills"}), "Low hills slowly rising into " + 
            "mountain ridges, the farther south you get.\n");

   add_item(({"ridge", "ridges"}), "Starting as low hills, these " +
            "ridges ends up, further south, as high mountains. The " +
            "Kharolis mountain range.\n");

   add_item(({"plain", "plains"}), "The flat plains of southern " +
            "Abanasinia, stretching out to the north of you. Low " +
            "grass and scattered bushes are the only kinds of " +
            "vegetation growing on these plains.\n");

   add_item("vegetation", "Low grass and scattered bushes.\n");

   add_item("grass", "Low grass covering the largest part of the " +
            "plains north you.\n");

   add_item("bushes", "Here and there, small groups of bushes break " +
            "the monotony of the flat plains.\n");
   
   OUTSIDE;

   add_exit(ROAD + "road1", "northeast", 0, 3);
   add_exit(VALLEY + "valley_road5", "southwest", 0, 2);
}

