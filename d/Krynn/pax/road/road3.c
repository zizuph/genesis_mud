/*
   Pax Tharkas, Road to Newports

   road5.c
   -------

   Coded ........: 95/04/28
   By ...........: Jeremiah

   Latest update : 2003/06/5
   By ...........: Blizzard

*/
/*
 * Revision history:
 * 25-10-99 by Boron: Added warfare support
 */


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit  "/d/Krynn/pax/road/road_base.c";
#define  QUALINESTI        "/d/Krynn/qualinesti/forest/" 

void
create_pax_room()
{
   /* Add warefare support */
   set_area_name(WAR_AREA_NEWPORT);

   set_short("Road on plains");
   set_long("@@long_descr");

   OUTSIDE;

   add_item(({"mountain", "mountains"}), "The Kharolis mountains " +
            "stretching from east to west, across the horizon. " +
            "They look quite inpenetrable, but maybe somewhere " +
            "there is a way over, or through, them.\n");

   add_item(({"plain", "plains"}), "The flat plains of southern " +
            "Abanasinia, stretching out to all sides of you. Low " +
            "grass and scattered bushes are the only kinds of " +
            "vegetation growing on these plains.\n");

   add_item(({"shimmering", "air", "mist", "mists"}), "Looking east, " +
            "across the plains, you see a shimmering in the air, " +
            "like mists or a haze rising above water. It is probably " +
            "the sea Newsea you can catch a glimpse of in the " +
            "distance.\n");

   add_item(({"forest", "canopy"}), "The forest visible is the " +
            "outskirts of the elven kingdom Qualinesti. It is " +
            "rumoured that deep within the forest lies the rich " +
            "and beautiful city of Qualinost, capital of the " +
            "Qualinesti elves.\n");

   add_item("vegetation", "Low grass and scattered bushes.\n");

   add_item("grass", "Low grass covering the largest part of the " +
            "plains around you.\n");

   add_item("bushes", "Here and there, small groups of bushes break " +
            "the monotony of the flat plains.\n");

   add_item("road", "A simple dusty road, running across the plains " +
            "southern Abanasinia.\n");

   add_exit(ROAD + "road4", "northeast", 0, 3);
   add_exit(ROAD + "road2", "southwest", 0, 3);
 // connection with Qualinesti
   add_exit(QUALINESTI + "nentrance", "west", 0, 3, 1);
   add_exit(QUALINESTI + "forest25", "northwest", 0, 3, 1);
}


string
long_descr()
{
   string ret_str;
   object shadow;

   ret_str = "You are standing on a road running across the open " +
             "plains of southern Abanasinia. Far to the south the " +
             "Kharolis mountains stretches across the horizon from " +
             "east to west. Northwest and west you can see the green " +
             "canopy of a huge forest. Eastwards, beyond the plains, " +
             "you see a strange shimmering in the air, like mist " +
             "rising above water. The road leads southwest towards " +
             "the mountains, and northeast across the open plains. " +
             "A barely noticable animal trail is leading west into " +
             "the woods. ";

   if(shadow = P("_dragon_shadow_", TO))
   {
      ret_str += "You see a huge shadow on the ground, slowly gliding " +
                 shadow->query_direction() + "wards.";
   }

   ret_str += "\n";

   return ret_str;
}
