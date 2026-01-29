/*
 *	/d/Gondor/ithilien/emyn-arnen/rrd1.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/ithilien/emyn-arnen/arnen_items.c";

#include <language.h>

#include "/d/Gondor/defs.h"

static object  Gate;

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("village");
    set_areaname("Emyn Arnen");
    set_land("Ithilien");
    set_extraline("This small by-way ends at a large wooden gate leading " +
    "into the large building. To the south the river disappears into " +
    "a large duct under the building.");
    add_item(({"road", "by-way", "branch"}), BSN(
    "This small by-way was probably used to supply those living in " +
    "the large building with provisions."));
    add_item(({"village", "houses", "ruins"}), BSN(
    "The village consists of several small stone houses opposite " +
    "a large building built with its back to the hill that " +
    "rises south of the plain."));
    add_item(({"building", "large building", "palace"}), BSN(
    "The large building is almost a small palace. It once had at least " +
    "three floors, but in places the top floors have fallen down onto " +
    "the lower ones. With its back, the building leans on the hill " +
    "south of the village."));
    add_item(({"hill", "hills", "emyn arnen"}), BSN(
    "The green hills west of the road are the hills of Emyn Arnen, the " +
    "land in southern Ithilien that was the home of the House of Hurin, " +
    "the house of the Stewards of Gondor. It rises between the road and " +
    "the Anduin, and was said to be the most beautiful part of Ithilien " +
    "before it fell under the Shadow."));
    add_item(({"duct",}), BSN(
    "The small river is several feet across and it must be quite deep. " +
    "It is quickly disappearing into the duct under the building. " +
    "Probably the river was meant to supply the inhabitants of the " +
    "building with water. You can see that at the entrance of the duct " +
    "several thick iron rods prevent anything larger than a small " +
    "animal from entering the building through the water."));
    add_item(({"river", "bank"}), BSN(
    "The small river is several feet across and it must be quite deep. " +
    "It is quickly disappearing into the duct under the building. " +
    "The bank of the river is rather low, so that it is possible " +
    "to enter the river rather easily."));
    
    add_exit(ITH_DIR + "emyn-arnen/vrd2",   "north", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/palace/kitchen", "southwest", 0, 1);
    (Gate = clone_object(ITH_DIR + "emyn-arnen/obj/kitchen_gate_out"))->move(TO);
}

string
short_desc()
{
    if (areatype == 8)
        return "A small road in "+LANG_ADDART(areadesc)+" in "+areaname+
            " in "+land;
    return ::short_desc();
}

int
do_enter(string str)
{
    if (!strlen(str))
        NFN0("Enter what?");

    if (str == "duct")
        NFN0("You cannot reach the duct from the bank of the river.");

    if (str == "river" || str == "water")
    {
        TP->move_living("into the river", ITH_DIR + "emyn-arnen/rivr1", 1);
        return 1;
    }
    NFN0("Enter what?");
}

public void
reset_room()
{
    ::reset_room();

    Gate->reset_door();
}

public void
init()
{
    ::init();

    add_action(do_enter, "enter");
}

