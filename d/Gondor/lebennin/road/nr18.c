/*
 *	/d/Gondor/lebennin/road/nr18.c
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/lebennin/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_road()
{
    set_area("southern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(8);
    set_areadesc("great plain");
    set_grass("green");
    set_extraline("The road runs in a long straight line across " +
        "the wide plain of southern Lebennin towards Pelargir upon " +
        "Anduin. Green fields lie to both sides, and in the east " +
        "shines the wide blue band of the Anduin. " +
        "A smaller road is running off westwards, circling the " +
        "city to the south just outside the city walls.");

    add_exit(LEB_DIR + "road/nr17",           "northeast", 0, 4);
    add_exit(PELAR_DIR + "streets/n_gate_out", "south",     0, 2);
    add_exit(LEB_DIR + "rroad/rr7",           "west",      0, 4);
   
    add_anduin("south");
    add_plain("city");
   
    add_item(({"city","pelargir" }), BSN(
       "Pelargir upon Anduin is the second largest city of Gondor "
     + "and the largest harbour of the realm. The northern city "
     + "gates are to the south and you can reach them by "
     + "following the road."));
    add_item(({"gate", "gates", "wall", "walls", "city gates",
        "city gate", "city wall", "tower", "towers" }), BSN(
        "The city gates of Pelargir can be seen to the south. "
      + "On each side of the gates stands a mighty tower, not "
      + "very high, but of enormous circumference. On the far "
      + "sides of the towers, the city wall continues."));

    add_ground();
    add_item(({"road"}), BSN(
       "This is an ancient well-crafted stone road that runs "
     + "through the eastern parts of Lebennin along the west "
     + "bank of the Anduin, connecting Pelargir in the south "
     + "with Minas Tirith in the north."));
    add_item( ({ "small road", "smaller road", }), BSN(
        "The small road is branching off from the main road here, " +
        "turning westwards to circle the city of Pelargir just " +
        "outside the city walls."));
}

