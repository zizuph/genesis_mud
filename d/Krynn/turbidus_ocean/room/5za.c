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
 
    add_item(({"rugged coastline","coastline","barren coastline",
       "northern wastes","wastes","hills","dry rolling hills","rolling hills"}),
       "To your south is a sheltered beach, beyond which stretches a rugged and " +
       "barren coastline, the beginning " +
       "of the vast Northern Wastes. Dry rolling hills make up the coastline before " +
       "you, with desolate sand dunes extending for leagues inland.\n");
    add_item(({"sand dunes","dunes","desolate sand dunes","inland"}),
       "Beyond the dry rolling hills begin great sand dunes that stretch far inland.\n");
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
    add_item(({"sea bed", "bed", "wreckage", "ship wreckage"}),
        "Not far beneath you is a clear sandy sea bed devoid of obstacles that could " +
        "cause damage to a moored ship. There is a bit of ship wreckage on the " +
        "sea bed you may be able to swim down to.\n");

    add_row_exit(ROOM + "5z", "west", 0, 1);
    add_row_exit(ROOM + "6zb", "northeast", 0, 1);
    add_row_exit(ROOM + "6za", "north", 0, 1);

    add_exit(ROOM + "5zauw", "down", "@@swim_down", 1, 1);
    add_swim_exit(ROOM + "5z", "west", "@@swim_bay", 4);
    add_wade_exit(ROOM + "beach2", "south", "@@wade_ashore", 2);

    add_cmd_item(({"down","water","to surface","up" }),
         ({"dive","swim"}),
        "If you want to swim up or down, just head in that direction!\n");


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(61);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The dangerous shoals and sandbars to your " +
        "south are beyond your sailing skills to navigate!\n");
    set_sailing_difficulty_message("You navigate skillfully through the " +
        "dangerous shoals and sandbars to the sheltered bay!\n");

    set_sink_path(ROOM + "5zauw");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

int
swim_down()
{
    if(this_player()->query_skill(SS_SWIM) > 29)
    {
       write("You dive down towards the sea bed.\n");
       return 0;
    }
    write("You try and dive down to the sea bed, but are unable to get very far " +
        "from the surface. You'll need to improve your swimming if you wish to swim deeper.\n");
    say(QCTNAME(TP) + " tries to dive down to the sea bed, however isn't a strong enough " +
          "swimmer to get far from the surface.\n");
    return 1;
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

    write("You swim with powerful strokes to your west.\n");
    say(QCTNAME(TP)+ " swims with powerful strokes to your west.\n");
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
        "a ship, with the sea bed largely devoid of obstacles with the exception " +
        "of a bit of ship wreckage. A sandy beach to your south allows " +
        "you to make landfall here. " +
        "Dangerous shoals and sandbars to your north form a natural barrier for " +
        "the bay that only experienced sailors would be able to navigate. "+
        query_sailing_difficulty_desc()+ "\n";
}