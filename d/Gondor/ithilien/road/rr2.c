/*
 *	/d/Gondor/ithilien/road/rr2.c
 *
 *	Coded 1993 by Elessar.
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("path along the forest's edge");
    set_area("northern");
    set_areaname("the forests");
    set_land("Ithilien");
    set_extraline("The path runs north and south between the river and the "+
        "forest. You spot some ruins out on the river to the southwest. "+
        "The forest dominates the eastern view, with tall larches and oak trees. "+
        "To the west of you the river Anduin flows quietly past. The "+
        "undergrowth along the river forces you to follow the old path.");
    add_item("path", BSN("The path runs north and south here along the " +
        "river and the forest. It does not look as if it is used very often."));
    add_item("ruins", BSN("They are ruins of ancient buildings of " +
        "stone, a city built upon the river Anduin. You see broken " +
        "bridges stretching partway across the river, tumbled walls " +
        "and corrupted towers."));
    add_item( ({ "river", "anduin", }), 
	"The mighty river Anduin flows past west of here, on its way " +
        "south to the ocean.\n");
    add_item( ({ "forest", "forests", }), BSN("The forests of Ithilien " +
        "are lovely to look upon; a refreshing smell of green herbs and " +
        "fair flowers is brought by the wind. The entire view to the " +
        "east is obscured by the forest."));
    add_item( ({ "gorse", "thorns", "briars", "trees", "undergrowth", }), 
	BSN("All along the eastern side of the path thick undergrowth is " +
        "preventing you from entering the forest. Gorse and low tough " +
        "thorns with intertwining branches, at least several yards thick, " +
        "are growing under briars and larger trees."));

    add_exit(ITH_DIR + "road/rr3", "north", 0, 3);
    add_exit(ITH_DIR + "road/rr1", "south", 0, 3);
}

