/*
 *	/d/Gondor/ithilien/road/rr8.c
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
    set_extraline("The path runs north and south through green fields and pastures " +
        "on the eastern bank of the Anduin. To the north, it crosses a stream on an " + 
        "ancient stone bridge. A pleasant smell of flowers and plants "+
        "is ever present as you walk along. The forest dominates the view to the "+
        "east, covering most of the sloping hillsides and ridges in the lands "+
        "that rise towards dark mountains on the east horizon. "+
        "To the west the mighty River Anduin flows quietly past from the "+
        "north towards the south. In the middle of the river you can see the " +
        "southernmost end of a large island that continues far to the north.");
    add_item("path","The path runs north and south here along the river and the\n"+
    "forest. It doesn't look as if it is used very often.\n");
    add_item(({"river","anduin","island"}),BSN(
        "The mighty river Anduin flows past west of here, on "+
        "its way south to its mouths in the Bay of Belfalas. " +
        "In the middle of the river you can see a large island."));
    add_item("forest","The forests of Ithilien are lovely to look upon; a refreshing\n"+
    "smell of green herbs and fair flowers is brought by the wind.\n"+
    "The entire view to the east is dominated by the forest.\n");
    add_item(({"bridge"}), BSN(
        "The ancient stone bridge crosses a stream that comes running " +
        "down from the hillsides to the east. The bridge has two arches " +
        "made of smoothly hewn stones that rest on a middle pier. The " +
        "farther of the two arches has been destroyed, so one would not " +
        "be able to cross the river here if not someone had put some wooden " +
        "planks across the gap."));
    add_item( ({ "stream" }), BSN(
        "Compared to the mighty Anduin, the stream is not big, but it is large enough " +
        "to block the way to the north if it were not for the bridge. You " +
        "estimate it is at least 20 yards across, and the current is " +
        "surprisingly strong. It would carry you far into the Anduin if you " +
        "were foolish enough to try swimming across the stream."));
    add_item(({"field","fields","pastures"}), BS(
        "The path runs through green fields on the east bank of the Anduin. " +
        "To the east, small groups of trees can be seen in the fields, " +
        "until in some distance the forests of northern Ithilien begin. " +
        "These fields must be very fertile, and there are still some " +
        "traces of cultivation, but evidently these fields have not seen " +
        "the scythe or the plough of a farmer for decades."));
    add_exit(ITH_DIR+"road/rr9", "north",     bridge, 4);
    add_exit(ITH_DIR+"road/rr7", "southeast",      0, 4);
}

public string
short_desc()
{
    return CAP(areadesc) + " in the " + area + " parts of " + areaname;
}
