/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_cliff4.c
 *
 *  The cliffs surrounding Del Rimmon in the Blackwall Mountains of
 *  Emerald continue to run parallel to the lake here. Just to the north
 *  are a band of orcs from the Army of Darkness.
 *
 *  Copyright (c) April 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allow us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("west");
    set_show_area_desc();

    set_extraline("The cliffs here rise nearly due west from the center"
                + " of the lake, which is faintly visible through the"
                + " tops of some of the forest trees. A bit to the"
                + " north, a trail of smoke rises from the edge of"
                + " the woods.");

    add_item( ({"center", "center of the lake"}), BSN(
        "Travelling just a bit to the south would place one at precisely"
      + " due west from the center of the lake of Del Rimmon."));
    add_item( ({"wood", "woods"}), BSN(
        "The slopes to the east which run down to the lake shore are"
      + " covered with tall trees, which have formed a forest around"
      + " Del Rimmon."));
    add_item( ({"edge", "edge of the woods"}), BSN(
        "There appear to be debris of some sort littering an area"
      + " close to the edge of the forest a ways to the north. Smoke"
      + " can be seen rising above the treetops."));
    add_item( ({"smoke", "coiling ribbon", "ribbon", "thin ribbon",
                "trail", "trail of smoke",
                "thin ribbon of smoke", "coiling ribbon of smoke",
                "thin coiling ribbon of smoke"}), BSN(
        "The smoke is rising in a thin coiling ribbon which suggests"
      + " that a campfire has been recently extinguished."));
    add_item( ({"debris"}), BSN(
        "The debris are too far away to identify, yet it looks as if"
      + " litter has been strewn about."));
    add_item( ({"litter"}), BSN(
        "It is not clear what sorts of debris are scattered to the"
      + " north. It is too far away."));
    add_item( ({"campfire"}), BSN(
        "From here it is uncertain that there is any campfire at all."
      + " Only to the north can the source of the rising smoke be"
      + " discovered."));

    add_cmd_item( ({"debris", "litter"}),
                  ({"search", "dig"}), BSN(
        "The debris are to the north, and far from your grasp here."));
    add_cmd_item( ({"smoke"}),
                  ({"search"}), BSN(
        "Even if you were close enough, that would not be possible."));

    add_exit(DELRIMMON_DIR + "lakeside/w_cliff5","north");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5b","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4b","east",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b","southeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff3","south");

    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "The cliff walls block your progress.\n");
} /* create_cliff_room */
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
