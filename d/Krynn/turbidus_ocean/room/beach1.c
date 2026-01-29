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

#ifndef HERB_MASTER
#define HERB_MASTER      "/d/Krynn/common/herbs/herb_master"
#endif

#define LIVE_I_CAN_FISH  "_live_i_can_fish"

string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

void
reset_sea_room()
{
    set_searched(0);

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

void
create_sea_room()
{
    set_short("secluded beach");
    set_long("You stand on the golden sands of a secluded beach. To your north " +
        "the waves from a sheltered bay gently wash on to the shore. To your " +
        "east the beach continues. " + get_time_desc()+
        "\n");

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
     
 
    add_exit(ROOM + "beach2", "east", 0, 1);
    add_wade_exit(ROOM + "5z", "north", "@@wade_bay", 4);

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(LIVE_I_CAN_FISH, "saltwater");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"beach","sand"}), 2);
}

int
wade_bay()
{
    write("You wade into the waters out into the bay.\n");
    say(QCTNAME(TP)+ " wades out into the waters of the bay.\n");
    return 0;
}
