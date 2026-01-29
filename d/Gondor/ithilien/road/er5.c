/*
 *	/d/Gondor/ithilien/road/er5.c
 *
 *	Modified by Olorin, December 1995
 *
 *	Book IV, Journey to the Cross-roads
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_CLIMB	20

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The long road winds down at the bottom of a deep valley, "
      + "which is falling in an ever-widening trough towards the Anduin in "
      + "the west. The road follows the course of a foul-reeking river "
      + "which flows westwards south of the road. Both valley and river "
      + "come out of a narrow gap in the towering mountain walls rising in "
      + "the east.");
    add_item(({"mountains","mountain-range","mountain","ephel duath",
        "mountain wall", "mountain walls", }), BSN(
        "The grey and omunous mountains towering in the east are the Ephel "
      + "Duath that mark the border of Mordor. You judge the mountains to be "
      + "between 5000 to 7000 feet tall, and you guess they are only about "
      + "a dozen miles away now."));
    add_item(({"valley", "trough", "banks", }), BSN(
        "The valley comes falling down from the Ephel Duath in the east "
      + "to the Anduin in the west. On both sides of the vally, there are "
      + "steep banks topped by green forests. It might be possible to climb "
      + "the northern bank here."));
    add_item("road", BSN("This is the road that in the high days of Gondor "
      + "had been made to run from the fair Tower of the Sun, Minas Anor, "
      + "which now is Minas Tirith, the Tower of Guard, to the tall Tower "
      + "of the Moon, Minas Ithil, which now is Minas Morgul in its "
      + "accursed vale. The road is well crafted, cobbled with stones and "
      + "lined with high banks, going winding down alongside the river from "
      + "the east to the west."));
    add_item(({"forest","forests","woods","flowers","trees","bushes"}), BSN(
        "The forests of Ithilien are lovely to look upon, consisting of small "
      + "woods of resinous trees, fir and cedar and cypress, oaks and ash-trees, "
      + "and among them grows bushes of olive and of bay, junipers and myrtles, "
      + "and beautiful sage flowers and marjorams and parsleys, asphodels and lilies."));
    add_item(({"river","morgulduin"}), BSN(
        "The Morgulduin runs from the accursed Morgul valley, and is "
      + "dark and foul to look upon, and there is a wrenching reek from it."));
    add_exit(ITH_DIR + "road/er6","east",0,2);
    add_exit(ITH_DIR + "road/er4","west",0,2);

    add_cmd_item(({"bank", "up", "northern bank", }), "climb", "@@climb_bank@@");
}

string
climb_bank()
{
    int     skill = (TP->query_skill(SS_CLIMB) - MIN_CLIMB);

    if (skill < 0)
        return "You are unable to climb the bank.\n";

    write("You climb up the northern bank of the valley.\n");
    set_dircmd("bank");
    TP->move_living("climbing up the northern bank", ITH_DIR + "nforest/hill");
    return "";
}

