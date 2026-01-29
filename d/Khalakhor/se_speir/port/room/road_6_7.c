/*
 * This is part of a road in Port Macdunn.
 *
 * Khail/Zima - July 25/97
 * Zima       - June 20/98 - recoded door functions
 */
#pragma strict_types
 
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "ktricircum.h"
#define  OTHER KIRK_ROOM+"kfoyer"
 
inherit ZOUTDOOR;
inherit ROADBASE;
 
public string
query_dir_to_jail()
{
    return "east";
}
 
public void
create_road()
{
    set_short("wide dirt road");
    set_long(
        "   You are standing before the grand entrance of the massive "+
        "stone structure to the north. A pair of heavy oak doors set "+
        "inside a set of concentric marble arches mark the portal of "+
        "the building, on which is sculpted an inscription in large "+
        "ornate letters. The side of a long stone hall with a thatched "+
        "roof runs alongside the wide dirt road on its south side.\n");
 
    add_item(({"structure","building","kirk"}),
        "It is a massive stone building rising high above the road, "+
        "a steeply-angled roof rising to a point above the entrance. "+
        "An emblem is sculpted in a circular niche high above the "+
        "doorway on the face of the wall. A set of concentric arches "+
        "mark the entrance of the structure, housing a pair of heavy "+
        "oak doors.\n");
    add_item(({"arch","arches","entrance","portal"}),
        "The entrance of the structure is marked by a set of "+
        "concentric arches made of marble, housing a pair of heavy "+
        "oak doors. There is an inscription sculpted along the wide "+
        "outer arch in large, ornate letters.\n");
    add_item("inscription",
        "It is written on the face of the entrance arch of the "+
        "structure. Perhaps you can read it.\n");
    add_cmd_item("inscription","read",
        "It reads: KIRK SEANCHAN TOR - ORDUGH SEAN RHIAN.\n");
    add_item("niche",
        "It is a large circular disk set in the face of the structure "+
        "high above the entrance arch. There is an emblem sculpted "+
        "within it.\n");
    add_item(({"emblem","tricircum"}), TRICIRCUM);
    add_item("hall",
        "It is a long stone hall, typical of the buildings of the "+
        "village, with stone walls and a thatched roof. It extends "+
        "along the road on its southern side.\n");
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_exit(ROOM + "road_7_7", "east");
    add_exit(ROOM + "road_5_7", "west");
 
    setup_outdoor("north", OTHER, ({"doors","door"}),
         "It is a pair of heavy oak doors set inside the pointed arch "+
         "of the entrance of the building.",
         "heavy oak doors",1);
}
 
void init()
{
   ::init();
   add_outdoor_actions();
}
