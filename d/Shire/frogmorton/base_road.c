/*
 * base road for Frogmorton
 * coded by Finwe, sept 1998
 * based on whitfurrows base file
 */
 
#include "/d/Shire/sys/defs.h"
inherit AREA_ROOM;
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_street() 
{
}
 
public void
create_area_room()
{
    area = "of";
    areaname = "Frogmorton";
    land = "East Farthing";
    areatype = 10;
    areadesc = "village";

    add_item(({"house","houses", "building", "buildings"}),
        "A few stand nearby, but very few are in the " +
        "village. They are made from mainly stone but one or " +
        "two seem to be made if wood.\n");
 
    add_item(({"burrow","burrows"}),
      "The burrows are dug into the ground and look like homes " +
        "for the poorest hobbits in Frogmorton. One small " +
        "window marks where each hole is and probably provides " +
        "barely enough light for the occupants. The burrows " +
        "look quite primitive.\n");
 
    add_item(({"smial","smials"}),
        "These large burrows are dug into the ground. They are " +
        "for the richest hobbits in Frogmorton. They have " +
        "several windows and doors and extend deep into the " +
        "hills.\n");
 
    add_item(({"lane","lanes", "road"}),
        "The lanes of Frogmorton are little more than " +
        "hard-packed dirt roads.  On either side of the lanes " +
        "are houses and burrows of the hobbits that live in " +
        "Frogmorton.\n");
 
    create_street();
}
