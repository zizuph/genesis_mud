/* 
 * Arman Kharas, February 2020
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>
#include "/d/Calia/sys/water.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

#define CHEST_KEY        "/d/Krynn/turbidus_ocean/obj/bishon_quest_key"
#define QUEST_PROP_FOUR  "_player_received_quest_four"
#define LIVE_I_CAN_FISH  "_live_i_can_fish"

string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

object key;
int key_taken;

void
reset_sea_room()
{
    set_searched(0);

    key_taken = 0;

    return;
}

nomask public string
get_time_desc()
{ 
    string desc = "";

    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "";
	break;
    case TOD_DAY:
	desc += "";
	break;
    case TOD_TWILIGHT:
	desc += "";
    break;
    case TOD_NIGHT:
	desc += "";
    break;
    default:
	break;
    }
    return desc;
}

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room()
{
    return 0; 
}

public void
sink(object ob)
{
    return;
}

mixed
search_sand(object searcher, string what)
{

    if (CAN_SEE_IN_ROOM(this_player()))
    {
        if(!key_taken)
        {
            // If don't have the quest from Bishon you can't find the key.
            if(!TP->query_prop(QUEST_PROP_FOUR))
	        return ("Your search through the sand fruitlessly, " +
                    "finding nothing of interest or anything you could " +
                    "salvage.\n");

            setuid();
            seteuid(getuid());
            key = clone_object(CHEST_KEY);
            key->move(TP, 1);
            key_taken = 1;

            say(QCTNAME(this_player())+ " found a key in the sand near " +
                 "the keel of the vessel!\n");
	    return ("Your search through the sand and find a key " +
                 "near the keel of the ship wreckage.\n");
        }
	else
	  {
	      return "You search through the sand, but do not find anything. " +
                  "It does however look like someone has searched through " +
                  "the sand recently.\n";
	  }
    }
  return 0;
}

void
create_sea_room()
{
    set_short("secluded beach");
    set_long("You stand on the golden sands of a secluded beach. To your north " +
        "the waves from a sheltered bay gently wash on to the shore. At the " +
        "eastern end of the beach is the bleached skeleton of small sailing vessel, " +
        "with a well-walked path from it leading in to the hills to your southeast. " +
        "To your west the beach continues. " + get_time_desc()+
        "\n");

    add_item(({"skeleton","wreck","vessel","sailing vessel","bleached skeleton"}),
        "At the eastern edge of the beach is the remains of a sailing vessel, " +
        "much of it stripped down to its keel, its frame bleached from the sun " +
        "and resembling a giant rib cage half buried in the sand. A " +
        "well-walked path leads from the wreck in to the hills to your southeast.\n");
    add_item(({"dry rolling hills","rolling hills","hills","northern wastes"}),
        "Beyond the beach along the coastline are dry rolling hills, the beginning " +
        "of the vast Northern Wastes. To your southeast you notice a well-walked " +
        "path lead in to the hills from the wreck of a sailing vessel here.\n"); 
    add_item(({"well-walked path","path"}),
        "To your southeast a path has been beaten from the beach here in to the " +
        "rolling hills.\n");
    add_item(({"secluded beach","beach","sand","sands","golden sands"}),
        "You stand on a secluded beach on the edge of a sheltered bay of the " +
        "Turbidus Ocean. The sands here are golden, with the waves from the ocean " +
        "gently washing over them.\n");
    add_item(({"waves"}),
        "The waves from the bay roll gently along the beach, tempered by the " +
        "shoals and sandbars naturally protecting the bay here.\n");
    add_item(({"dangerous shoals","shoals","sandbars"}),
        "The entry to the bay to your north is riddled with shoals and sandbars " +
        "that protect the beach from the aggression of the Turbidus Ocean.\n"); 
 
    add_exit(ROOM + "beach1", "west", 0, 1);
    add_exit(ROOM + "campsite", "southeast", "@@enter_campsite", 1);
    add_wade_exit(ROOM + "5za", "north", "@@wade_bay", 4);

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(LIVE_I_CAN_FISH, "saltwater");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    add_search(({"sand", "golden sand", "wreckage", "wreck", "vessel",
"keel", "sailing vessel","bleached skeleton","skeleton" }),
        10, "search_sand", 1);

    reset_sea_room();
}

int
enter_campsite()
{
    write("After a few steps down the trail you come to an impassable rockslide and " +
        "return to the beach.\n");
    return 1;
}

int
wade_bay()
{
    write("You wade into the waters out into the bay.\n");
    say(QCTNAME(TP)+ " wades out into the waters of the bay.\n");
    return 0;
}
