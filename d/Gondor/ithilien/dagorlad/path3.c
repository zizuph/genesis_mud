/*
 *	/d/Gondor/ithilien/dagorlad/path3.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 5-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(9);
    set_areadesc("desert");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("This is the desolation that lies before Mordor; " +
        "a land defiled, diseased beyond all healing. Gasping pits " +
        "and poisonous mounds are everywhere and seem to continue " +
        "up to the great mountains that rise in the south.\n");
    add_item(({"mountains","mountain-range","mountain","ephel duath",
        "ered lithui"}), 
        "To the south great mountains rise out of the desolation. " +
        "Out of their feet are flung huge buttresses and broken hills " +
        "that are about a dozen miles away.\n");
    add_item(({"desert", "desolation", "ground"}), 
        "The ground is covered with high mounds of crushed and powdered " +
        "rock, great cones of earth fire-blasted and poison-stained, " +
        "and in between gasping pools choked with ash and crawling " +
        "muds, sickly white and grey, as if the mountains have vomited " +
        "the filth of their entrails upon the lands about.\n");
    add_item(({"mounds", "mound", "cone", "cones"}), 
        "Foul fumes are leaking out of the slag mounds.\n");
    add_item(({"pit", "pits", "pools"}), 
        "The holes are cold and dead, many of them are filled with a " +
        "foul sump of oily many-coloured ooze at the bottom.\n");
    add_item(({"path"}), 
        "Across the desolation, a narrow path is running " +
        "from north to south.\n");
    add_exit(ITH_DIR + "dagorlad/path4", "north",     0, 5);
    add_exit(ITH_DIR + "dagorlad/path2", "south",     0, 5);
}
