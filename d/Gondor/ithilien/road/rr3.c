/*
 *	/d/Gondor/ithilien/road/rr3.c
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
    set_areadesc("path along the east bank of the Anduin");
    set_area("northern");
    set_areaname("the forests");
    set_land("Ithilien");
    set_extraline("The path runs north and south between the river and the "+
        "green forests of North Ithilien. A pleasant smell of flowers and plants "+
        "is ever present as you walk along. The forest dominates the view to the "+ 
        "east, covering most of the sloping hillsides and ridges in the lands "+
        "that rise towards dark mountains on the east horizon. "+
        "To the west the mighty River Anduin flows quietly past from the "+
        "north towards the south.");
    add_item( ({"path", "bank", }), BSN(
        "The path runs north and south here along the bank and the forest. " +
        "It does not look as if it is used very often. The bank slopes down " +
        "to the river to the west."));
    add_item("ruins", BSN(
        "They are ruins of ancient buildings of stone, a city built upon "+
        "the river Anduin. You see broken bridges stretching partway across "+
        "the river, tumbled walls and corrupted towers."));
    add_item( ({ "river", "anduin", }), 
        "The mighty river Anduin flows past west of here, on its way " +
        "south to the ocean.\n");
    add_item( ({ "forest", "forests", }), BSN(
        "The forests of Ithilien are lovely to look upon; a refreshing smell " +
        "of green herbs and fair flowers is brought by the wind. The entire " +
        "view to the east is obscured by the forest."));
    add_item("mountains", "You catch a glimpse of dark peaks beyond the forests.\n");
    add_item( ({ "hillsides", "ridges", }), BSN(
        "Ithilien has an uneven terrain, sloping down from the mountains "+
        "in the east, with many ridges and hillsides shaped by nature. "+
        "Mostly it is all covered by green, lush forests."));
    add_exit(ITH_DIR+"road/rr4", "north", 0, 3);
    add_exit(ITH_DIR+"road/rr2", "south", 0, 3);
}

