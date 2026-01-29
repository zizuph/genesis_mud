/*
 *	/d/Gondor/ithilien/road/rr7.c
 *
 *	Coded 1993 by Olorin.
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
    set_areadesc("a path along the east bank of the Anduin");
    set_area("western");
    set_areaname("North Ithilien");
    set_land("Ithilien");
    set_treetype("cypress");
    set_extraline("The path runs north and south through fields between " +
        "the river and the green forests of North Ithilien. A pleasant " +
        "smell of flowers and plants is ever present as you walk along. " +
        "The forest dominates the view to the east, covering most of the " +
        "sloping hillsides and ridges in the lands that rise towards dark " +
        "mountains on the east horizon. To the west the mighty River Anduin " +
        "flows quietly past from the north towards the south.");
    add_item("path","The path runs north and south here along the river and the\n"+
    "forest. It doesn't look as if it is used very often.\n");
    add_item( ({ "river", "anduin", }), BSN("The mighty river Anduin " +
        "flows past west of here, on its way south to the ocean. You " +
        "spot green fields on the far side, and in the middle of the " +
        "river a little further north, there is a small islet, with a " +
        "fortress built on its southmost end."));
    add_item( ({ "forest", "forests", }), BSN(
        "The forests of Ithilien are lovely to look upon; a refreshing " +
        "smell of green herbs and fair flowers is brought by the wind. " +
        "The entire view to the east is dominated by the forest."));
    add_item( ({ "field", "fields", "pastures", }), BSN(
        "The path runs through green fields on the east bank of the " +
        "Anduin. To the east, small groups of trees can be seen in the " +
        "fields, until in some distance the forests of northern Ithilien " +
        "begin. These fields must be very fertile, and there are still " +
        "some traces of cultivation, but evidently these fields have not " +
        "seen the scythe or the plough of a farmer for decades."));
    add_item("bank", BSN(
        "The bank slopes down to the river to the west. It clearly shows " +
        "signs of a variable water-level in the river, as the last few " +
        "feet are bare dirt, with no green growths."));
    add_exit(ITH_DIR+"road/rr6", "south", 0, 4);
    add_exit(ITH_DIR+"road/rr8", "northwest", 0, 4);
}

public string
short_desc()
{
    return CAP(areadesc) + " in the " + area + " parts of " + areaname;
}
