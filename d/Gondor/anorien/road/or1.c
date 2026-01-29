/*
 *  /d/Gondor/anorien/road/wr1.c
 *
 *  Coded 1992 by Elessar.
 *
 *  Modification log:
 *  30-Jan-1997, Olorin:  General revision.
 *  
 *  Added exits into Anorien plains. 
 *  Varian 2016
 */

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#pragma strict_types

public void    reset_room();

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("long, green");
    set_extraline("The road continues east towards Osgiliath, the ruined "
      + "city upon the River Anduin. To the south is the great Outer "
      + "Walls surrounding the Fields of Pelennor, the Rammas Echor. "
      + "Northwest this road connects with the West Road again, just "
      + "north of the gates."); 
    add_item( ({ "ruins", "osgiliath", }), BSN(
        "The ruins of the eastern parts of Osgiliath are visible to " +
        "the east. It is hard to make out details from here, save " +
        "that all the buildings are completely destroyed and only little " +
        "remains of them now."));
    add_item( ({ "gate", "rammas", "rammas echor", "wall", }), BSN(
        "The Rammas Echor is the great outer wall of Minas Tirith, " +
        "encircling all of the Pelennor. The northeastern gate, that " +
        "guards the road leading to Osgiliath, is to the southwest."));
    set_no_exit_msg(({"southwest","south","southeast"}),
        "You attempt to walk through the Rammas Echor, but you " +
        "notice the wall is far too solid for you to do that.\n");
    add_exit(ANO_DIR + "road/or2", "east",     0, 3);
    add_exit(ANO_DIR + "road/wr1", "northwest",0, 3);
    add_exit(ANO_DIR + "plains/an15w11n","northeast",0,3,1);
    add_exit(ANO_DIR + "plains/an14w11n","north",0,3,1);
    add_exit(PEL_DIR + "noutgate", "west",0,5,1);
    reset_room();
}

public void
reset_room()
{
    object  soldier;

    if (!objectp(soldier = present("soldier")))
	soldier = clone_npc(soldier, NPC_DIR + "gsoldier");
}

string
query_dir_to_gate()
{
    return "northwest";
}

/*
 This was used while the plains were under construction. Now open
 Varian - August 2016

int
block()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You should be able to enter the plains of Anorien soon!\n");
    return 1;
}

*/