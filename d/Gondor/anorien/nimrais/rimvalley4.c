/*
 *	/d/Gondor/anorien/nimrais/rimvalley4.c
 *
 *	Coded by Olorin
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(2);
    set_areadesc("hillside in a valley");
    set_grass("sparse ");
    set_area("central");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_extraline("You are in a south-going valley on the north side "
      + "of the White Mountains. The slopes in the valleysides are quite "
      + "steep here, compared to the looks of the hillsides to the "
      + "north. A small stream trickles into the valley from the south, "
      + "then running off north. A few bushes clamber to the hillside, "
      + "but you doubt you can climb up by them. The valley continues "
      + "south and north.");
    add_item("stream","The stream is quite small and cold, originating from the snowy peaks in\n"+
        "the White Mountains to the south.\n");
    add_item(({"slope","slopes"}), BSN(
        "To both sides of the valley, steep slopes are rising. They are " +
        "covered with loose rubble and small stones so that it is impossible " +
        "to climb them."));
    add_exit(ANO_DIR + "nimrais/rimvalley3","north",0,2);
    add_exit(ANO_DIR + "nimrais/rimvalley5","south",0,3);
    add_prop(OBJ_I_CONTAIN_WATER,1);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("moderate")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("hills")), }),
                  ({ "hill", "hillsides", "slope", "slopes", }), 3);
}

public int
do_climb(string str)
{
    NFN("Climb what?");
    if (!strlen(str))
        return 0;

    str = LOW(str);
    switch (str)
    {
    case "slope":
    case "slopes":
    case "hillside":
    case "hill":
        write(BSN("The slopes are exceedingly steep and covered with loose rubble "
          + "so that you cannot climb them."));
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

public void
init()
{
    ::init();
    add_action(do_climb, "climb");
}

