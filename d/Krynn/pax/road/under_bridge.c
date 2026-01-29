/*
   Pax Tharkas, Road to Newports, under the wooden bridge.

   under_bridge.c
   --------------

   Coded ........: 95/05/09
   By ...........: Jeremiah

   Update        : 95/10/25
   By ...........: Boron

   Latest Update : 06/06/05
   By............: Navarre


*/
/*
 * Revision history:
 * 27-10-96 By Teth:    Added Herbs
 * 25-10-99 by Boron:   Added warfare support
 * 05-06-06 by Navarre: Changed FILTER_LIVE to FILTER_PLAYERS
 *                      Since npcs walk here now.
 */


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit "/d/Krynn/pax/road/road_base.c";

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "riverbank", }) );

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
        live = FILTER_PLAYERS(inv);

        if(sizeof(live))
            return;

        skeleton_found = 0;
        skeleton->remove_object();
    }
}


void
create_pax_room()
{
    /* Add warefare support */
	set_area_name(WAR_AREA_NEWPORT);

    set_short("Under wooden bridge");
    set_long("You are standing among some low bushes, under a wooden " +
      "bridge. A small creek flows gently along here. The solid " +
      "stone socles supporting the bridge are clearly visible " +
      "through the flowing water. High green grass grows along " +
      "both sides of the creek, and the low bushes cover the " +
      "slopes leading back up to the road.\n");

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
    
    add_cmd_item(({ "up", "bridge", "wooden bridge" }),
        ({ "crawl", "climb" }), "@@do_climb" );
         
    add_exit(ROAD + "road4", "up", 0);

    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"high grass","grass","herbs","creek",
        "path",}), 4);

    enable_reset(200);
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

string
do_climb(string where)
{
    write("You climb up the wooden bridge.\n");
    set_dircmd("up");
    TP->move_living("climbing the bridge", ROAD + "road4", 0, 0);
    
    return "";
}







