/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/sw_cliff4.c
 *
 *  Copyright (c) January 1998, by Cooper Sherry (Gorboth)
 *
 *  The ridge of cliffs surrounding Del Rimmon curves northwest to
 *  southeast here as it winds. Some careless orc has lost his shoe
 *  here.
 *
 *  Emerald Conversion: November 2000
 *
 *  Changes:
 *  Cotillion - 2020-08-31
 *  - Fixed shoe cloning logic
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public void    reset_room();
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("southwest");
    set_show_area_desc();

    set_extraline("A long ridge of cliffs dominates the view as it"
                + " travels in a long curving path around the shores"
                + " of the lake to the northwest and southeast.");

    add_item( ({"long ridge of cliffs", "long ridge", "ridge",
                "ridge of cliffs", }), BSN(
        "The ridge high above seems to plateau somewhat, leaving"
      + " little guess as to what might lie in its crags."));
    add_item( ({"shore", "shores"}), BSN(
        "The shores of Del Rimmon are not visible from here, yet"
      + " perhaps lie a short distance as one travels down the slope"
      + " of the hill to the northeast."));

    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff5","northwest");
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff3","southeast");
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3b","north",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2b","east",0,1,1);

    set_no_exit_msg( ({ "south", "southwest", "west" }),
        "The cliff walls block your progress.\n");

    reset_room();
} /* create_cliff_room */

/*
 * Function name: reset_room
 * Description  : Here we add a pair of shoes to the room each
 *                reset which some careless orc has lost
 */
public void
reset_room()
{
    object  shoes;

    if (!present("shoe", TO) )
    {
        shoes = clone_object(DELRIMMON_DIR + "obj/arm/shoes");
        shoes->add_prop(OBJ_I_BROKEN, 1);
        shoes->add_prop_obj_i_broken();

        shoes->move(TO);
    }
} /* reset_room */
/*
 * Function name: init
 * Description  : Add actions to the player.
 */
public void
init()
{
    ::init();

    add_action(em_climbing_hook, "climb");
} /* init */
