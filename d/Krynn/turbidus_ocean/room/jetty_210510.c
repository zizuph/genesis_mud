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
	desc += "To your east the rays of the rising sun " +
            "illuminate two ramshackle buildings - one a store " +
            "where you may buy or sell wares with no questions asked, " +
            "the other a tavern that looks as hungover as its patrons " +
            "in the morning light.";
	break;
    case TOD_DAY:
	desc += "To your east stand two ramshackle buildings - one a store " +
            "where you may buy or sell wares with no questions asked, " +
            "the other a tavern that looks as hungover as its patrons " +
            "in the harsh light of day.";
	break;
    case TOD_TWILIGHT:
	desc += "The sun setting in the east silhouettes two ramshackle " +
            "buildings - one a store where you may buy or sell wares with " +
            "no questions asked, the other a tavern awakening for a rowdy " +
            "night of drunken debauchery!";
    break;
    case TOD_NIGHT:
	desc += "To your east you can barely make out in the darkness of " +
            "night two ramshackle buildings - one a store where you may buy " +
            "or sell wares with no questions asked, the other a tavern " +
            "alive with rowdy patrons. ";
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
    set_short("Reefcutter's Jetty");
    set_long("You find yourself at a dock for pirates and corsairs " +
        "to sell their ill-gotten loot and drink rum! Cleverly built " +
        "amongst dangerous jagged rocks, only a skilled navigator " +
        "would be able to make their way here, providing a form of " +
        "natural protection from all but the most experienced " +
        "and persistent naval captain. " + get_time_desc()+
        "\n");
 
    add_item(({"ramshackle buildings","buildings","building"}),
        "To your east you can make out two buildings, one a store " +
        "and the other a tavern.\n");
    add_item(({"store","fence"}),
        "To your east you make out a small ramshackle building " +
        "that is used by pirates and corsairs to sell their wares.\n");
    add_item(({"tavern"}),
        "To your east you make out a small ramshackle building " +
        "that is used by pirates and corsairs as a tavern where they " +
        "can revel in drunken lawless debauchery!\n");         

    add_row_exit(ROOM + "4t", "west", 0, 1);
    add_exit(ROOM + "jetty_shop", "store", 0, 1);
    add_exit(ROOM + "tavern", "tavern", 0, 1);

    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(70);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The jagged rocks before Reefcutter's Jetty " +
        "are beyond your ability to navigate! Without a doubt you would " +
        "sink your ship if you sailed in that direction.\n");
    set_sailing_difficulty_message("Navigating the jagged rocks around the " +
        "dock takes the skills of a professional mariner, but you are up " +
        "to the challenge!\n");
}
