/*
 * Base file for road in elven city Thalandrone
 * Finwe, july 2001
 */
 
#include "/d/Shire/cypress/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/cypress/std/room/room_tell";
inherit "/cmd/std/command_driver";
inherit "/d/Shire/cypress/thalandrone/base_common";
 
//define ROOM_TELL_TIME  random(180)+30
void create_road_room() {}

string where = "northern";  /* northern part of town */

public void create_area_room()
{

//    what_time = "It is @@day_desc@@ in Esgaroth. ";
//    ring_count = "third";    
    set_area("in the");
    set_areaname("unknown ring");
    set_land("Thalandrone");
    set_areatype(0);
    set_areadesc("street");
    add_item(({areadesc}),
        "The " + areadesc + " is constructed of white stone " +
        "blocks. They are set into the ground and are slightly " +
        "textured. The " + areadesc + " is broad, allowing many " +
        "elves to walk side by side.\n");
    add_item(({"buildings", "building"}),
        "The buildings are all made of white stone blocks and " +
        "are various sizes and floors. They are all grand " +
        "looking and very stately, even the smallest buildings. " +
        "Soaring towers reach for the sky on the largest " +
        "buildings and most of the buildings are surrounded " +
        "with beautiful gardens and fountains. The buildings " +
        "are individual works of art, the such as never been " +
        "seen before.\n");
    add_item(({"house", "houses"}),
        "All the houses are stately structures. They are " +
        "surrounded with gardens and fountains. The buildings " +
        "are made of white stone blocks that have been polished " +
        "and decorated with exquisite detail.\n");
    add_item(({"roofs", "roof"}),
        "The roofs of the buildings are mostly flat, permitting " +
        "elves a place to retire to.\n");
    add_item("eaves",
        "There are no visible eaves.\n");
    add_item(({"shingles"}),
        "There are no shingles.\n"); 
    add_item(({"chimney", "chimnies"}),
        "There are no visible chimnies.\n");
    add_item("sky",
        "The sky is alive with sunlight.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("A cool breeze blows from off the lake.");
    add_room_tell("Dark clouds roll overhead, blocking the sun.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("The leaves rustle in the breeze.");
    add_room_tell("A quick movement catches your eye, then is gone.");
    add_room_tell("Gentle, soothing sounds echo from a nearby fountain.");
    add_room_tell("Soothing music resounds from nearby.");
    add_room_tell("The lilting voice of an elf fills the air.");
    add_room_tell("Some leaves fall gently to the ground.");

    create_road_room();
    set_add_all_rooms();

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
init()
{   
    ::init();
//    add_action("drink_it",      "drink");
}

string road_desc1()
{
    return "The " + areadesc + " is wide and passes through " +
    "Thalandrone. Impressive buildings are scattered throughout " +
    "the city. Tall trees grow everywhere, hiding most of the city. ";
}

string road_desc2()
{
    return "The wide " + areadesc + " is made of large stone " +
    "blocks. Gardens surround the magnificent buildings of " +
    "Thalandrone. Fountains fill the air with a quiet sound of " +
    "bubbling brooks. ";
} 

string road_desc3()
{
    return "Ancient trees shade this exquisite " + areadesc + 
    ". Splendid buildings line the " + areadesc + ", a tribute " +
    "to the exquisite workmanship of the elves. Quiet gardens " +
    "are scattered about area. ";
} 

string road_desc4()
{
    return "Splendid buildings line the " + areadesc + 
    ", which is wide and well used as it runs through " +
    "Thalandrone. Lovely gardens surround the buildings, and " +
    "ancient trees grow everywhere. ";
} 

string road_desc5()
{
    return "The " + areadesc + " sparkles in the light as it " +
    "passes through Thalandrone. It is framed by lovely " +
    "buildings, gardens, and fountains. ";
}


public string
long_desc()
{
//    string time;
    string desc;
    
//    time  = CLOCK->query_time_of_day(),
    desc = CAP(query_short()) + ". ";
/*
    if (!(CLOCK->query_war()))
    {
	desc += describe_time(time);
    }
    else 
    {
	desc += describe_war(time);
    }
*/
    if (strlen(extraline))
	desc += (" " + extraline);
    if (functionp(vbfc_extra))
	desc += " " + vbfc_extra();
    return (desc);
}



int
block_rd()
{
    if (this_player()->query_wiz_level()) return 0;

        write("A spell has been cast here, preventing " +
            "visitors to go that way.\n");
    return 1;
}
