/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_cliff6.c
 *
 *  Here the cliffs have reached a bend in their range, extending
 *  south and west from a cleft at the bend. This is the northeastern
 *  most point in the area here along the northwestern slopes of
 *  the Blackwall Mountains surrounding Del Rimmon.
 *
 *  Copyright (c) July 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";

#include <ss_types.h>     /* for SS_CLIMB */
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define        SKILL_NEEDED    30  /* for climbing */

/* prototypes */
public void    create_cliff_room();
public int     em_climbing_hook(string str);
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with area presets
 */
void
create_cliff_room()
{
    set_loc(3);
    set_side("northwest");

    set_extraline("Extending a ways further to the south, the range"
                + " of steep cliffs jogs dramatically from what"
                + " appears to be a rather straight run to the west."
                + " A deep cleft runs up the cliffs here, marking the"
                + " turning point in the rock walls.");

    add_item( ({"run", "straight run", "run to the west", 
                "rather straight run to the west"}), BSN(
        "West of here, the cliffs march into the distance along what"
      + " appears to be a very straight run."));
    add_item( ({"range", "range of steep cliffs", "cliff range"}), BSN(
        "The cliffs run for what appears to be a distance to the"
      + " west. Rounding a bend here, they extend for a bit to the"
      + " south before falling away to accomodate the lakeshore."));
    add_item( ({"bend", "turning point", "point"}), BSN(
        "A deep cleft marks the turning point in the cliffs where"
      + " the range to the west jogs dramatically to the south."));
    add_item( ({"lakeshore"}), BSN(
        "The lakeshore is not visible from this vantage point."));
    add_item( ({"cleft", "deep cleft", "deep clefts"}), BSN(
        "The deep cleft which runs up the cliffs here marks the"
      + " turning point in the cliff range. It looks quite deep,"
      + " and jagged along its edges."));
    add_item( ({"edges", "edge", "edge of the cleft",
                "edges of the cleft"}), BSN(
        "The cleft looks to be roughly the width of an average"
      + " human, with many bits of stone protruding from the"
      + " jagged edge along each side."));
    add_item( ({"jagged edge", "bits of stone", "each side"}), BSN(
        "The edges of the cleft look as if they might provide an"
      + " interesting challenge for an experienced climber."));
    add_item( ({"ledge"}), BSN(
        "The ledge is not visible from this vantage point."));

    add_cmd_item( ({"cleft", "deep cleft"}),
                  ({"search"}), BSN(
        "The cleft is far too big to search appropriately, as its"
      + " depths appear to be unreachable. It may provide an"
      + " interesting climb, however."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff7","south");
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff5","west");

    set_no_exit_msg( ({ "northwest", "north", "northeast", "east",
                        "southeast" }),
        "The cliffs rise both to the north and east, blocking your"
      + " progress.\n");
} /* create_cliff_room */

/*
 * Function name: em_climbing_hook
 * Description  : here we redefine the hook in the cliff_room master
 * Arguments    : string str - what the player typed after 'climb'
 * Returns      : 1 - tried to climb cleft,
 *                0 - otherwise
 */
int
em_climbing_hook(string str)
{
    notify_fail("The cliffs here look far too perilous to attempt"
                + " any climbing.\n");

    if (!strlen(str))
    {
        return 0;
    }

    if (str != "cleft" && str != "deep cleft")
    {
        return 0;
    }

    else
    {
        if (TP->query_fatigue() < 50)
        {
            WRITE("You are too tired to try to climb up the cleft.");
            return 1;
        }

        if (TP->query_skill(SS_CLIMB) < SKILL_NEEDED + random(5))
        {
            WRITE("You attempt to climb up the sides of the deep"
                + " cleft, but cannot successfully navigate the"
                + " difficult handholds.");
            SAY(" attempts to scale the deep cleft in the cliff face,"
              + " but seems to be unable to get very far.");

            TP->add_fatigue(-50);
            return 1;
        }

        WRITE("Carefully planting your feet in the base of the cleft,"
            + " you slowly work your way up the cleft in the rock,"
            + " skillfully navigating the difficult handholds afforded"
            + " by the jagged edges. Perhaps twenty feet from what"
            + " would seem to be the top of the cliff, the cleft ends"
            + " abruptly where the rock is steeply undercut, making"
            + " any further progress impossible. As you make your way"
            + " back to the base of the cliff, you notice a ledge"
            + " which extends along the cliffs to the west, high"
            + " above the ground.");
        SAY(" skillfully climbs up to the top of the cleft, where "
            + TP->query_pronoun() + " stops for a moment to gaze"
            + " around before returning slowly to the base of"
            + " the cliff.");

        TP->add_fatigue(-50);
        return 1;
    }

    NFN0("The cliffs here look far too perilous to attempt any"
       + " climbing.");
} /* em_climbing_hook */

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
