/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_cliff5.c
 *
 *  The cliffs which surround the valley of Del Rimmon in the Blackwall
 *  Mountains of Emerald have nearly reached their northeasternmost
 *  point here. A strange pit extends from the base of the cliffs
 *  here. What could it be?
 *
 *  Copyright (c) August 1998, by Cooper Sherry (gorboth)
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
 * Description  : allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("northwest");
    set_show_area_desc();

    set_extraline("Below these tall cliffs which run directly west and"
                + " east from here, a broad and shallow pit extends"
                + " from the base of the stone walls. The forest to"
                + " the south looks thinner here, trailing away"
                + " against the sheer rock faces to the southeast.");

    add_item( ({"trees which grow further west"}), BSN(
        "The trees which grow further to the west appear to occupy a"
      + " denser forest than that which grows directly south"
      + " of here."));
    add_item( ({"denser forest"}), BSN(
        "The trees to the west and southwest appear to grow more"
      + " thickly than those directly south of here."));
    add_item( ({"pit", "broad pit", "shallow pit",
                "broad and shallow pit"}), BSN(
        "The origins of this pit are not readily apparent. It appears"
      + " to be old enough to have weathered some erosion, and is"
      + " filled somewhat with stones from the cliff sides."));
    add_item( ({"erosion"}), BSN(
        "The ground around the pit is well packed and sunken somewhat"
      + " which would seem to indicate that if it were created by"
      + " forces other than nature, they must have occured quite a long"
      + " while ago."));
    add_item( ({"stone", "stones", "stones from the cliff sides"}), BSN(
        "The stones which fill the bottom of the pit are scattered"
      + " haphazardly about. It is likely that they fell from the"
      + " cliff sides above."));
    add_item( ({"sides", "side", "cliff sides", "cliff side"}), BSN(
        "The sides of the cliff are rent and cracked, which would"
      + " more than likely account for the stones which lie piled"
      + " in the pit here at the cliff base."));
    add_item( ({"ground", "cliff base", "base of the cliff",
                "base of the cliffs", "base of these cliffs"}), BSN(
        "The ground at the base of these cliffs is marked by a broad"
      + " and shallow pit that extends a short distance from the"
      + " stone walls."));
    add_item( ({"stone walls", "stone wall", "tall cliff",
                "tall cliffs"}), BSN(
        "The stone walls of the cliffs rise high above this slope."));
    add_item( ({"base", "base of the stone walls"}), BSN(
        "A low and shallow pit extends from the base of the stone"
      + " walls here. It seems unclear what may have caused such a"
      + " pit to form."));
    add_item( ({"forest", "forest to the south"}), BSN(
        "The forest to the south thins somewhat from the trees"
      + " which grow further west. It appears as if the trees fall"
      + " away altogether to the southeast, where the cliffs have"
      + " curved around to meet them."));
    add_item( ({"sheer rock faces", "faces", "rock faces",
                "rock faces to the southeast",
                "sheer rock faces to the southeast"}), BSN(
        "The cliffs appear to have curved around to the southeast,"
      + " where they halt the progress of the forest which extends"
      + " a ways in that direction before dying away."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff6","east");
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff7","southeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3","south",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3b","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff4","west");

    set_no_exit_msg( ({ "northwest", "north", "northeast" }),
        "The cliffs prevent any northern movement.\n");
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
