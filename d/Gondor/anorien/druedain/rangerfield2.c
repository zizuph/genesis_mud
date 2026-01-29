/*
 * /d/Gondor/anorien/druedain/rangerfield2.c
 * 
 * modified for new rangers: Tigerlily, Feb. 6, 2004
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void   reset_room();

#ifndef  NEW_RANGERS_OPEN 
static object Herbalist;
#endif

public void
create_area_room()
{
    set_areatype(2);
    set_areadesc("clearing");
    set_area("western");
    set_areaname("Druedain Forest");
    set_land("Gondor");
    set_grass("soft, light green");
    set_treetype("large, tall oaks");
    set_extraline("A few flowers and plants grow in this nice little clearing in "
		  + "the forest. The sweet fragrance of the flora makes you feel "
		  + "relaxed. On all sides of the clearing large oak trees grow, "
		  + "and block your way, save south where you can see an opening "
		  + "between the trees.");
    add_exit(DRUEDAIN_DIR + "rangerfield", "south", 0);
    add_item("flowers", 
	     "There are lovely flowers of many colours growing in the field.\n");
    add_item("plants",
	     "There are some plants growing in the field. You might even find herbs "
	     + "among them, if you search well enough.\n");
    add_item("trees", "Mostly oak trees grow in this part of the forest.\n");
    add_item("opening", "The oak trees do not grow so close together to the north.\n");
    reset_room();
}

public void
reset_room()
{
#ifndef  NEW_RANGERS_OPEN 
    if (!objectp(Herbalist))
    {
        Herbalist = clone_object(RANGER_DIR + "npc/herbalist");
        Herbalist->arm_me();
        Herbalist->move(TO);
    }
#endif
}

