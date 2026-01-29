/*
 *	/d/Gondor/ithilien/road/rr10.c
 *
 *	Coded 1993 by Olorin.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance.
 *  July 2016, Varian: Added access across the ford to Cair Andros
 * 
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/anorien/defs.h"
#include <stdproperties.h>
#include <macros.h>

public int    bridge();
public void    reset_room();

static object  Ranger;

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("a path on the east bank of the Anduin");
    set_area("western");
    set_areaname("North Ithilien");
    set_land("Gondor");
    set_extraline("The path runs southeast on the eastern bank "
	+ "through fields between the river and the green forests "
        + "of North Ithilien. The path once continued to the north " 
        + "across a turbulent stream, but heavy waters have washed " 
        + "and made further passage in that direction impossible. "
        + "To the west, you can that the waters of the Anduin are "
        + "a little calmer and shallow, presenting a natural ford " 
        + "you could use to cross and reach the island of Cair "
        + "Andros. A pleasant smell of flowers and plants "
        + "is ever present as you walk along. The forest dominates "
        + "the view to the east, covering most of the sloping "
        + "hillsides and ridges in the lands that rise towards "
        + "dark mountains at the eastern horizon.");
    add_item(({"path"}), BSN("The path runs southeast here along the "
        + "river bank through green fields west of the tree covered "
        + "slopes. Once it continued over a stone bridge to the "
        + "northwest, crossing a broad river that joins the Anduin "
        + "here. Since the bridge has been destroyed, it is not "
        + "possible to cross it. Perhaps that is the reason why "
        + "the path does look as if it is not used frequently."));
    add_item(({"river","anduin","stream","great river","water"}), BSN(
        "The mighty river Anduin flows past west of here, on "+
        "its way south to its mouth in the Bay of Belfalas. " +
        "In the middle of the broad river, you can see a large island. " +
        "To the north a broad stream comes running down from the hills " +
        "and has washed out an old bridge before it joins the Anduin.\n"));
    add_item(({"forest","slopes","hillsides","hills"}), BSN(
        "The forests of Ithilien are lovely to look upon; a refreshing "+
        "smell of green herbs and fair flowers is brought by the wind. "+
        "The entire view to the east is dominated by the forests " +
        "covering the slopes that run up to the Mountains of Shadow " +
        "visible many leagues away.\n"));
    add_item(({"island","cair andros"}), BSN(
        "You can see Cair Andros, a large forested island that stands " +
        "in the middle of the Anduin as it flows past to the west. At the " +
        "southern end of the island, a tall stone fortress stands guard, " +
        "watching over the river and surrounding lands.\n"));
    add_item(({"ford","passage"}), BSN(
        "It seems as if the Anduin runs a little shallower and calmer " +
        "here, with a natural ford forming a passage between Ithilien and " +
        "the island of Cair Andros.\n"));
    add_item(({"field"}), BSN("The path runs through a green field "
        + "on the east bank of the Anduin. To the east, small "
        + "groups of trees can be seen in the fields, until in "
        + "some distance the forests of northern Ithilien begin. "
        + "These fields must be very fertile, and there are still "
        + "some traces of cultivation, but evidently these fields "
        + "have not seen the scythe or the plough of a farmer for "
        + "decades."));
    add_item(({"bridge","wooden bridge","old bridge"}), 
        BSN("Once upon a time, the path continued north across an old " +
            "wooden bridge which has since been broken and washed " +
            "away by the broad stream. There are also what appear " +
            "to be the remains of two piers, which allowed for river " +
            "traffic to land in this part of Ithilien."));
    add_item(({"pier","piers"}), BSN(
        "These piers were made of wood, but are now useless and destroyed. " +
        "You suspect that once upon a time, the men of Gondor used them " +
        "when river traffic was more common along the Anduin.\n"));

    add_exit(ITH_DIR+"road/rr10", "north", bridge, 4);
    add_exit(ITH_DIR+"road/rr9",  "southeast", 0, 4);
    add_exit("/d/Gondor/anorien/cairandros/e_ford","west","@@ford@@",5,1);

    reset_room();
}

public int
ford()
{
    find_living("varian")->catch_tell("****  " +
        capitalize(this_player()->query_real_name()) + " is visiting " +
        "Cair Andros  ****----\n\n");
    write("You enter the ford and begin to wade across the Anduin.\n");
    say(QCTNAME(TP) + " wades west into the river.\n");
    return 0;
}

public int
bridge()
{
    write("The bridge is broken! You cannot go north here, the stream " +
    "is too rough and blocks your way!\n");
    return 1;
}

public string
short_desc()
{
    return CAP(areadesc) + " in the " + area + " parts of " + areaname;
}

public void
reset_room()
{
    if (!objectp(Ranger))
    {
        Ranger = clone_object(NPC_DIR + "i_ranger");
        Ranger->arm_me();
        Ranger->set_random_move(20);
        Ranger->move_living("down to earth", TO);
    }
}

/*
    Just a block from entering Cair Andros, was used while it was under
    construction. - Varian, August 2016

int
block()
{
    if (this_player()->query_wiz_level()) return 0;
    write("You should be able to enter the ford across the Anduin soon!\n");
    return 1;
}

*/
