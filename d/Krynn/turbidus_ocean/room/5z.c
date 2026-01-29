#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../local.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "nearshore", }) );

void
reset_sea_room()
{
    set_searched(0);

    return;
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
 
    add_item(({"rugged coastline","coastline","barren coastline", "shoreline",
       "northern wastes","wastes","hills","dry rolling hills","rolling hills"}),
       "To your south beyond the bay is a rugged and barren shoreline, the southwestern " +
       "tip of the Northern Wastes known as 'Destiny's Hand'. " +
       "Dry rolling hills make up the coastline, populated by little other than " +
       "wild goats and desert eagles.\n");
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north stretches the Turbidus Ocean - a massive body of water " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"bay", "entry", "sheltered bay"}),
        "You are at the southern end of a sheltered bay, naturally protected to " +
        "your north by dangerous shoals and sandbars. Here would make a good " +
        "place to moor a ship and make landfall.\n");
    add_item(({"sheltered beach","beach","sheltered sandy beach","sandy beach"}),
        "Near you to your south is a sandy beach that you could likely wade to " +
        "from here.\n");
    add_item(({"dangerous shoals","shoals","sandbars"}),
        "The entry to the bay to your north is riddled with dangerous shoals and sandbars " +
        "that would require skilled navigation to bypass and get to the sheltered " +
        "sandy beach on the edge of the bay.\n"); 

    add_row_exit(ROOM + "5za", "east", 0, 1);
    add_row_exit(ROOM + "6y", "northwest", 0, 1);
    add_row_exit(ROOM + "6z", "north", 0, 1);

    add_swim_exit(ROOM + "5za", "east", "@@swim_bay", 4);
    add_wade_exit(ROOM + "beach1", "south", "@@wade_ashore", 2);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(61);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The dangerous shoals and sandbars to your " +
        "south are beyond your sailing skills to navigate!\n");
    set_sailing_difficulty_message("You navigate skillfully through the " +
        "dangerous shoals and sandbars to the sheltered bay!\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

int
wade_ashore()
{
    write("You wade towards the beach to your south.\n");
    say(QCTNAME(TP)+ " wades towards the beach to your south.\n");
    return 0;
}

int
swim_bay()
{
    if(TP->query_skill(SS_SWIM) < 30)
    {
        write("You don't have the swimming skill to do more than " +
            "dog paddle here!\n");
        return 1;
    }

    write("You swim with powerful strokes to your east.\n");
    say(QCTNAME(TP)+ " swims with powerful strokes to your east.\n");
    return 0;
}

string
short_descr()
{
    return "in a sheltered bay near a sandy beach";
}
 
string
long_descr()
{
    return turbidus_sea_desc() + "You are in a sheltered bay suitable for mooring " +
        "a ship. A sandy beach to your south allows you to make landfall here. " +
        "Dangerous shoals and sandbars to your north form a natural barrier for " +
        "the bay that only experienced sailors would be able to navigate. "+
        query_sailing_difficulty_desc()+ "\n";
}