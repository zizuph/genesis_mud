/*
 *	/d/Gondor/anorien/nimrais/rimvalley3.c
 *
 *	Coded by Elessar, 1992
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
    string *area_herbs;

    set_areatype(2);
    set_areadesc("hillside in a valley");
    set_grass("thick");
    set_area("central");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_extraline("You are in a south-going valley on the north side "
      + "of the White Mountains. The slopes in the valleysides are "
      + "quite steep here, compared to the looks of the hillsides to "
      + "the north. A small stream runs north out of the valley here. "
      + "Following the hillside south, you realize they get even "
      + "steeper there.");
    add_item("stream", BSN("The stream is quite small and cold, "
      + "originating from the snowy peaks in the White Mountains to "
      + "the south."));
    add_item(({"slope","slopes"}), BSN(
        "To both sides of the valley, steep slopes are rising. They are "
      + "covered with lose rubble and small stones so that it is "
      + "impossible to climb them."));
    add_exit(ANO_DIR + "nimrais/trolls/path1", "north", 0, 2);
    add_exit(ANO_DIR + "nimrais/rimvalley4",   "south", 0, 3);
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);

    area_herbs = HERB_MASTER->query_herbs("moderate");
    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                     ONE_OF_LIST(area_herbs), ONE_OF_LIST(area_herbs), }),
                  ({ "slope", "slopes", "bushes", }), 3);
                      
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
        write(BSN("The slopes are exceedingly steep and covered with "
          + "lose rubble so that you cannot climb them."));
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

