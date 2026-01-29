/*
   Pax Tharkas, Road to Newports, under the wooden bridge.

   under_bridge.c
   --------------

   Coded ........: 95/05/09
   By ...........: Jeremiah

   Latest update : 96/10/27
   By ...........: Teth (added herbs)

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;

#include "/d/Krynn/common/herbsearch.h"

int    skeleton_found = 0; /* 0 : skeleton NOT found */
object skeleton;

void
reset_pax_room()
{
   set_searched(random(2));
   {
   object *inv, *live;

   inv = ({});
   inv = all_inventory(TO);
   live = FILTER_LIVE(inv);

   if(sizeof(live))
      return;

   skeleton_found = 0;
   skeleton->remove_object();
 }
}


void
create_pax_room()
{
   set_short("Under wooden bridge");
   set_long("You are standing among some low bushes, under a wooden " +
            "bridge. A small creek flows gently along here. The solid " +
            "stone socles supporting the bridge are clearly visible " +
            "through the flowing water. High green grass grows along " +
            "both sides of the creek, and the low bushes cover the " +
            "slopes leading back up to the road. A path enters a grim " +
            "forest to the west.\n");
         
   OUTSIDE;


   add_item(({"bridge", "wooden bridge"}), "The bridge is built of " +
            "solid timber. Its pillars are supported by stone " +
            "socles, planted in the water, deep into the bottom of " +
            "the creek. It looks like a very solid contruction.\n");

   add_item("creek", "A small creek flowing across the plains of " +
            "southern Abanasinia. The water flows from northwest " +
            "and continues towards southeast, probably running " +
            "out into Newsea.\n");  

   add_item(({"socle", "socles"}), "Solid stone socles, planted deep " +
            "into the bottom of the creek, supporting the wooden " +
            "bridge spanning the creek.\n");

   add_item("water", "The water flowing along here looks very clear " +
            "and fresh.\n");

   add_item(({"high grass", "grass"}), "Fresh green grass grows " +
            "knee high along both sides of the creek.\n");

   add_item("path", "The path seems to be old and not well-used.\n");

   add_item(({"bush", "bushes", "low bushes"}), "@@bush_descr");

   add_exit(ROAD + "road4", "up", 0);
   add_exit(WAYRETH + "forest/forest01", "west");

    seteuid(getuid(TO));
    set_search_places(({"high grass","grass","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(KRHERB + "jewelweed");
    add_herb_file(KRHERB + "solinaith");
    add_herb_file(KRHERB + "bkd_sedge");
    add_herb_file(KRHERB + "bur_reed");
    add_herb_file(KRHERB + "cattail");

    reset_pax_room();
}


init()
{
   ::init();
   add_action("drink_water", "drink");
}


string
bush_descr()
{
   if(skeleton_found)
   {
      tell_room(TO, QCTNAME(TP) + " looks through the low bushes.\n", TP);
      return "You look through the low bushes, but find nothing of " +
             "interest.\n";
   }

   skeleton_found = 1;
   tell_room(TO, QCTNAME(TP) + " looks through the low bushes, and " +
             "discovers a small skeleton.\n", TP);
   skeleton = clone_object(POBJ + "kender_skeleton");
   skeleton->move(TO);
   return "As you look through the bushes, you suddenly discover " +
          "a small skeleton.\n";
}


int
drink_water(string what)
{
    if ((what == "water") || (what == "from creek") ||
       (what == "water from creek"))
    {
       if (TP->drink_soft(TP->drink_max() / 16,0))
       {
          write("You drink some water from the creek and " +
                "feel refreshed.\n");
          say(QCTNAME(TP) + " drinks from the creek.\n");
       }
       else
          write("Hmm, you don't feel thirsty at all at the moment.\n");
       return 1;
    }
    return 0;
}


void
someone_arrives(object who)
{
   tell_room(TO, QCTNAME(who) + " arrives, crawling down from the " +
             "bridge.\n", who);
}









