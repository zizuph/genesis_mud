/*
 *	/d/Gondor/ithilien/road/rr9.c
 *
 *	Coded 1993 by Olorin.
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public int
bridge()
{
    write("You walk over the stone bridge.\n");
    return 0;
}

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("a path along the east bank of the Anduin");
    set_area("western");
    set_areaname("North Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("The path runs northwest to south on the eastern bank " +
        "through fields between the river and the green forests of North Ithilien. " +
        "To the south a stream flows down from the hillsides to the east; the path " +
        "crosses that stream on an ancient stone bridge. " +
        "A pleasant smell of flowers and plants "+
        "is ever present as you walk along. The forest dominates the view to the "+
        "east, covering most of the sloping hillsides and ridges in the lands "+
        "that rise towards dark mountains at the eastern horizon. "+
        "To the west the mighty River Anduin flows quietly past from the "+
        "north towards the south. In the middle of the river you can see a large island.");
    add_item("path", BSN("The path runs northwest to south here along the " +
        "river bank through green fields west of the tree covered slopes. " +
        "It does not look as if it is used frequently."));
    add_item(({"island","river","anduin"}), BSN(
        "The mighty river Anduin flows past west of here, on its way " +
        "south to its mouth in the Bay of Belfalas. In the middle of the " +
        "river you can see a large island."));
    add_item(({"forest","slopes","hillsides","hills"}), BSN(
        "The forests of Ithilien are lovely to look upon; a refreshing "+
        "smell of green herbs and fair flowers is brought by the wind. "+
        "The entire view to the east is dominated by the forests covering " +
        "the slopes that run " +
        "up to the Mountains of Shadow visible many leagues away."));
    add_item(({"field"}), BSN(
        "The path runs through green fields on the east bank of the " +
        "Anduin. To the east, small groups of trees can be seen in the " +
        "fields, until in some distance the forests of northern Ithilien " +
        "begin. These fields must be very fertile, and there are still some " +
        "traces of cultivation, but evidently these fields have not seen " +
        "the scythe or the plough of a farmer for decades."));
    add_item( ({ "bridge", }), BSN(
        "The ancient stone bridge crosses a stream that comes running " +
        "down from the hillsides to the east. The bridge has two arches " +
        "made of smoothly hewn stones that rest on a middle pier. The " +
        "nearer of the two arches has been destroyed, so one would not " +
        "be able to cross the river here if someone had not put some " +
        "wooden planks across the gap."));
    add_item(({"stream"}), BSN(
        "Compared to the mighty Anduin, the stream is not big, but it is " +
        "large enough to block the way to the south if it were not for the " +
        "bridge. You estimate it is at least 20 yards across, and the " +
        "current is surprisingly strong. It would carry you far into the " +
        "Anduin if you were foolish enough to try swimming across the stream."));

    add_exit(ITH_DIR + "nforest/sstream12", "east",           0, 4);
    add_exit(ITH_DIR + "road/rr8",          "south",     bridge, 4);
    add_exit(ITH_DIR + "road/rr10",         "northwest",      0, 4);
}

public string
short_desc()
{
    return CAP(areadesc) + " in the " + area + " parts of " + areaname;
}
