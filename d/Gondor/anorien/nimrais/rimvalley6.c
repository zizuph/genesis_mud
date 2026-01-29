/*
 * 	Modification log:
 *      Stern, 17-Mar-2000, added ability to drink water.
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(5);
    set_areadesc("narrow valley");
    set_grass("sparse ");
    set_area("central");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_extraline("The valley comes to an end here, so you are in "
      + "a cul-de-sac. All around you are sheer mountain cliffs that "
      + "are certainly unclimbable. Only to the northeast there is an exit.");
    add_item(({"mountain","mountains","cliffs","cliff","hillsides"}), BSN(
        "Rocky cliffs almost completely surround you. They rise vertically for "
      + "a good many furlongs on all sides, and are so sheer and featureless "
      + "that they are impossible to climb."));
    add_item("stream", BSN(
        "You seem to have reached the source of the small stream. It comes out "
      + "of a small hole in the rock wall to the south and runs northeast in "
      + "the middle of the valley."));
    add_item(({"hole","rock wall","source"}), BSN(
        "The small stream that runs down the valley springs out of a "
      + "hole in the rock wall to the north here. The hole is almost hidden "
      + "behind a small group of bushes growing in front of it."));
    add_item(({"ground"}), BSN("The ground is rocky and barren, only at the "
      + "foot of the cliff to the north, there are some bushes, and some "
      + "sparse growth of grass."));
    add_item(({"grass"}), BSN("There is no grass growing here, only at "
      + "the foot of the cliff rising to the north, a few blades are growing "
      + "close to some bushes."));
    add_item(({"bush", "bushes", }), BSN("The only bushes are growing at "
      + "the foot of the cliff that forms the northern wall of this valley, "
      + "on both sides of the small stream that comes running out of the "
      + "hole behind the bushes."));
    add_exit(ANO_DIR + "nimrais/quest/base","northeast",0,3);
    add_prop(OBJ_I_CONTAIN_WATER,-1);
    set_drink_from("stream");    
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
    case "cliff":
    case "cliffs":
    case "mountain":
    case "mountains":
    case "rock wall":
        write(BSN("The rocky cliffs rise vertically and are smooth and "
          + "featureless so that it is impossible to climb them."));
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

public int
do_enter(string str)
{
    if (!strlen(str))
        return 0;

    str = LOW(str);
    switch (str)
    {
        case "cave":
        case "hole":
            write("Stooping low, you enter the cave.\n");
            say(QCTNAME(TP)+" disppears behind some bushes.\n");
            set_dircmd(str);
            TP->move_living("M", ANO_DIR + "nimrais/cave/entrance");
            say(QCNAME(TP) + " arrives.\n");
            return 1;
            break;
        default:
            NFN("Enter what?");
            break;
            return 0;
    }
}

public void
init()
{
    ::init();
    init_drink();   
    add_action(do_climb, "climb");
    add_action(do_enter, "enter");
}

