/* -*- Mode: C -*-
 *
 * cross.c
 *
 * Skippern 20(c)01
 *
 */
inherit "/d/Gondor/common/lib/area_room";

#include "../../defs.h"

int
blocked()
{
    // uncomment when the area is opened
    // return 0;

    if (this_player()->query_wiz_level())
    {
	write("The road is closed by the orders of Prince Imrahil.\n");
	return 0;
    }
    write("The road is closed by the orders of Prince Imrahil.\n");
    return 1;
}

void
create_area_room()
{
    set_areatype(AREATYPE_ROAD);
    set_land("Belfalas");
    set_areadesc("field");
    set_area("western");
    set_areaname("Dor-en-Ernil");

    set_extraline("You are in the middle of a cross road. To the west the " +
		  "road climbs over some small hills, and to the " +
		  "northeast and southeast the road climbs up valleys. " +
		  "A sign post stands here.");

    add_item("cross", "Three roads meets here, one way goes west, one goes " +
	     "southeast, and one northeast.\n");

    add_item( ({ "sign", "sign post" }), 
	      "\t+====================================+\n" +
	      "\t|                                    |\n" +
	      "\t|                 <>                 |\n" +
	      "\t|                                    |\n" +
	      "\t|                    to Erech        |\n" +
	      "\t|                      +             |\n" +
	      "\t|                    /               |\n" +
	      "\t|  to Dol Amroth <-X                 |\n" +
	      "\t|                    \\               |\n" +
	      "\t|                      +             |\n" +
	      "\t|                     Dor-En-Ernil   |\n" +
	      "\t|                      to Pelargir   |\n" +
	      "\t|                                    |\n" +
              "\t|                 <>                 |\n" +
              "\t|                                    |\n" +
              "\t+====================================+\n" +
	      "\t                 |  |\n" +
	      "\t                 |  |\n" +
	      "\t                 |  |\n");

    add_exit(DOL_OTHER + "outside/close", "west", 0, 1);
    add_exit("/d/Gondor/erech/vale/A11", "northeast", 0, 1);
    add_exit(TO_BELFALAS, "southeast", &blocked(), 1);
}
