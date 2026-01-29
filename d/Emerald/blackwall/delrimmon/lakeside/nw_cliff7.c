/*
 * /d/Emerald/blackwall/delrimmon/lakeside/nw_cliff7.c
 *
 * Walking north from the lakeshore, the area opens up here, revealing
 * an area beneath the cliffs in which one may walk. These cliffs ring
 * the lake of Del Rimmon in the Blackwall Mountains of Emerald, and offer
 * some nice sight-seeing.
 *
 * Copyright (c) July 1998, by Cooper Sherry (Gorboth)
 *
 * Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public int     woods();
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allow us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("northwest");
    set_show_area_desc();

    set_extraline("A few trees grow directly up to the walls of stone"
                + " to the south, only to back away from the cliffs"
                + " here and to the north, where an aisle of sorts"
                + " exists between the trees of the forest, and the"
                + " feet of the cliff faces.");

    add_item( ({"edge of the cliff", "edge", "cliff edge"}), BSN(
        "The ground runs up to the edge of the cliff here, where"
      + " an aisle of sorts marks where the trees have stopped"
      + " their growth."));
    add_item( ({"trees of the forest"}), BSN(
        "The trees rise to the west and south, but fall back from"
      + " the edge of the cliff."));
    add_item( ({"few trees", "trees to the south",}), BSN(
        "The trees which grow up to the cliff sides form a very thin"
      + " band of green which separates this area below the cliffs"
      + " with the shoreline to the south."));
    add_item( ({"thin band", "thin band of green"}), BSN(
        "Though thin, the trees to the south are rather dense with"
      + " vegetation and undergrowth, making visibility difficult"
      + " as one looks south."));
    add_item( ({"vegetation", "undergrowth",
                "vegetation and undergrowth"}), BSN(
        "Vegetation and undergrowth runs thickly through the forest,"
      + " and particularly so in the band of trees which runs to"
      + " the south."));
    add_item( ({"walls", "walls of stone", "stone walls"}), BSN(
        "The cliffs tower above the forest and lakeshore to the"
      + " south. It appears as if they begin to angle somewhat as"
      + " one follows them north, perhaps rounding a bend in that"
      + " direction."));
    add_item( ({"bend"}), BSN(
        "The cliffs to the north are a ways off yet, and one cannot"
      + " clearly see which direction they run from here."));
    add_item( ({"aisle", "aisle of sorts"}), BSN(
        "The trees do not grow directly up to the wall of the cliffs,"
      + " except to the south, where a thin row separates this area"
      + " from the lakeshore. It would seem as if avalanches and"
      + " debris from the cliff have done well to prevent much"
      + " vegetation from growing close to the cliff wall."));
    add_item( ({"lakeshore",}), BSN(
        "The lakeshore is not clearly visible through the dense"
      + " vegetation to the south."));
    add_item( ({"debris", "debris from the cliff"}), BSN(
        "Bits of stone and debris have evidently fallen down from"
      + " above to pile at the base of the cliffs here."));
    add_item( ({"bits", "bits of stone", "bits of stone and debris",
                "pile", "base of the cliffs", "base"}), BSN(
        "It would seem as if debris such as this have prevented"
      + " the trees from successfully growing up to the edge of"
      + " of the cliffs."));
    add_item( ({"feet", "feet of the cliffs"}), BSN(
        "There are debris littered among the feet of the cliffs."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff6","north");
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore3","south",woods,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore2","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff5","northwest",0,1,1);
    set_no_exit_msg( ({ "southeast", "east", "northeast" }),
        "The walls of the cliff block your path.\n");
} /* create_cliff_room */

/*
 * Function name: woods
 * Description  : tell the player that they have passed through a
 *                row of trees as they walk south of here
 * Returns      : 0
 */
public int
woods()
{
    WRITE("Walking south, you pass through a row of trees on the way"
        + " down the slope.");

    return 0;
} /* woods */
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
