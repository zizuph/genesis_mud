/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood5.c
 *
 *  A steep embankment rises to the west here, where the tree clad
 *  slopes surrounding Del Rimmon in the Blackwall Mountains have
 *  been disturbed by the passing of destructive feet.
 *
 *  Copyright (c) April 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 *  Prototypes
 */
public int     climb_embankment();

/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with forest presets
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("west");
    set_show_area_desc();

    set_extraline("The slope of the hillside steepens sharply to the"
                + " west, where an embankment rises up from the"
                + " grassy ground.");

    add_item( ({"embankment", "steep embankment"}), BSN(
        "The embankment to the west angles steeply in what looks"
      + " to be a rough climb. Dirt and stones clutter the slope"
      + " in that direction."));
    add_item( ({"dirt"}), BSN(
        "The dirt along the steep embankment to the west looks"
      + " to have been recently churned by passing feet."));
    add_item( ({"stones", "stone"}), BSN(
        "The stones which lie in the steep embankment to the"
      + " west look as if they have been unearthed by the"
      + " passage of someone or something."));
    add_item( ({"dirt and stones"}), BSN(
        "The dirt and stones along the steep embankment to the"
      + " west look somehow disturbed."));
    add_item( ({"climb", "rough climb"}), BSN(
        "The slope of the embankment is steep and rugged. Travel"
      + " in that direction is sure to be tiresome work."));
    add_item( ({"ground", "grassy ground"}), BSN(
        "The mosses along the ground here look to have been"
      + " recently trampled by the passage of some person or"
      + " animal."));
    add_item( ({"prints", "print", "footprints", "footprint"}), BSN(
        "The footprints look to have come from the direction of"
      + " the lakeshore to the east. Signs of passage continue"
      + " up a steep embankment to the west."));
    add_item( ({"signs", "sign", "sign of passage",
                "signs of passage"}), BSN(
        "The embankment to the west clearly shows signs that"
      + " someone or something has passed up through the dirt"
      + " and stones to the west."));

    add_cmd_item( ({"print", "prints", "footprints", "footprint",
                    "ground", "grassy ground", "embankment",
                    "steep embankment", "stones", "stone",
                    "dirt", "dirt and stones"}),
                  ({"search"}), BSN(
        "The footprints are very vague in the mosses and undergrowth"
      + " of the forest. You notice that they appear to have come"
      + " from the east, and travel up the embankment to the west."));
    add_cmd_item( ({"print", "prints", "footprint", "footprints"}),
                  ({"follow"}), BSN(
        "The footprints lead both to the west and the east."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1b","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1", "northeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore5","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore4", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4b", "southwest",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5b", "west",
             climb_embankment, 10, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff1", "northwest",
             check_sitting,1,1);
} /* create_tree_room */

/*
 * Function name: climb_embankment
 * Description  : give the player a message about how rough the
 *                climb up the embankment is.
 * Arguments    : none
 * Returns      : 0
 */
public int
climb_embankment()
{
    WRITE("You trudge up the difficult slope, taking care not to"
        + " turn an ankle on the many loose stones in the dirt.");

    return 0;
} /* climb_embankment */
