/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_shore3.c
 *
 *  Here the lakeshore of Del Rimmon ends abruptly, running up
 *  against the sheer cliff faces of the Blackwall Mountains. This is the
 *  northernmost point along the shoreline of the west bank,
 *  and the river flows to the east where the remnants of the
 *  rapids jettison their current into the lake.
 *
 *  Copyright (c) September 1997 by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 *  Added fishing     : August 2021 (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeshore.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Prototypes
 */
public int     woods();

/*
 * Function name: create_lakeshore
 * Description  : allows us to create the room with area presets
 */
void
create_lakeshore()
{
    set_loc(1);
    set_side("northwest");

    set_extraline("The shoreline ends abruptly here where sheer cliffs"
                + " have taken rise, towering above the bank to"
                + " the east. The ground turns to mud before the"
                + " feet of the cliff, where a small pool of"
                + " water has secluded itself from the rest of"
                + " the lake. To the north, a row of trees grows"
                + " almost directly up to the side of the cliffs.");

    add_item( ({ "wall", "walls", "wall of the cliff",
                 "walls of the cliff", "cliff wall", "cliff walls",
                 "sheer cliff", "sheer cliffs", "eastern cliff",
                 "eastern cliff", "cliff face", "face",
                 "face of the cliff", "face of the cliffs",
                 "east", "nearest cliff", "nearest cliff face" }), BSN(
        "The shore ends directly to the east, where steep cliff"
      + " walls rise from the mud to tower overhead."));
    add_item( ({"row of trees"}), BSN(
        "The trees to the north grow close together, but seem to"
      + " be less dense than those which crowd up to the lake shore"
      + " further to the south."));
    add_item( ({"ground", "feet", "feet of the cliff", "cliff feet"}),
        BSN(
        "The pebbles which run along the beach stop short of"
      + " the cliff sides to the east, where muddy terrain"
      + " surrounds a shallow pool beneath the rock face."));
    add_item( ({"mud", "muddy ground", "muddy terrain", "terrain",
                "sides", "side of the pool", "sides of the pool"}), 
        BSN("The muddy ground which surrounds the shallow pool"
      + " seems to have been disturbed somehow. There are deep"
      + " grooves along its surface."));
    add_item( ({"groove", "grooves", "deep groove", "deep grooves"}),
        BSN("The grooves in the mud would seem to indicate that a"
      + " very heavy object of some kind was dragged from the pool"
      + " onto shore. There are many footprints beside the grooves."));
    add_item( ({"footprints", "prints", "print", "footprint"}), BSN(
        "These prints have dried, and look to be perhaps a week"
      + " old. In most cases, they have trampled one another, making"
      + " it difficult to identify what might have made them. There"
      + " do seem to be a few clear prints closer to the cliff,"
      + " however."));
    add_item( ({"clear print", "clear prints"}), BSN(
        "The wide heel and cruel nail marks along the toe"
      + " impressions of these prints are unmistakable. Orcs"
      + " have been here."));
    add_item( ({"pool", "secluded pool", "pools", 
                "shallow pool", "small pool", "pool of water"}),
        BSN("This pool is connected to the lake, but does not"
      + " receive influence from its current. Muddy terrain"
      + " spreads out from its sides."));
    add_item( ({"cliffs", "cliff", "head", "heads", "blackwall mountains",
                "top", "tops"}), BSN(
        "The towering cliffs of the Blackwall Mountains rise abruptly from the"
      + " steep slopes surrounding the lake. Their jagged tops"
      + " collide with the sky in all directions. Directly to the"
      + " east, the nearest cliff face frowns down upon this"
      + " shore, making travel in that direction impossible."));

    add_cmd_item( ({"pool", "secluded pool", "pools", "shallow pool",
                    "small pool", "pool of water"}),
                  ({"wade", "dive", "swim", "enter"}), BSN(
        "You wade into the small pool, and the water reaches your"
      + " waist. You notice that this depth seems to extend out"
      + " into the lake, which would allow for the passage of"
      + " a small craft. Finding nothing more, you trudge back onto"
      + " dry land."));
    add_cmd_item( ({"pool", "secluded pool", "pools", "shallow pool",
                    "small pool", "pool of water"}),
                  ({"search", "dig"}), BSN(
        "You search around in the shallow pool of water, but"
      + " only succeed in discovering a great deal of very"
      + " wet mud."));
    add_cmd_item( ({"pool", "secluded pool", "pools", "shallow pool",
                    "small pool", "pool of water"}),
                  ({"drink"}), BSN(
        "The water of the pool is very brown and murky. It does"
      + " not look clean enough to drink."));
    add_cmd_item( ({"under water", "below water", "beneath pool",
                    "beneath surface", "beneath the surface of the pool",
                    "below surface", "below the surface"}),
                  ({"dive", "swim"}), BSN(
        "You attempt to dive below the surface of the water in"
      + " what seems to be a rather shallow pool. The mud at the"
      + " bottom has been churned up so much that it is impossible"
      + " to see anything, and you cannot seem to feel anything"
      + " which is out of the ordinary. You emerge dripping, and"
      + " rather dirty, from the pool."));
    add_cmd_item( ({"cliff", "cliffs", "cliff face", "cliff side",
                    "cliffside"}),
                  ({"climb", "scale"}), BSN(
        "The sides of the cliff are sheer and vertical, often"
      + " undercut, so that climbing without ropes and hooks"
      + " would be impossible, and even with them, beyond your"
      + " skill."));
    add_cmd_item( ({"mud", "muddy terrain", "muddy ground", "ground"}),
                  ({"search"}), BSN(
        "You find that the mud surrounding the pool has been"
      + " disturbed recently."));


    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff7","north",woods,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore2","west");
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3","northwest",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "northeast", "east" }),
        "The walls of the cliff block your path.\n");
    set_no_exit_msg( ({ "southeast", "south" }),
        "Taking a few steps into the water, you decide against"
      + " wandering further into the lake.\n");
} /* create_lakeshore */

/*
 * Function name: woods
 * Description  : tell the player that they have passed through a
 *                row of trees on their way north
 * Returns      : 0
 */
public int
woods()
{
    WRITE("Marching north up the slope, you pass through a thin row"
        + " of trees.");

    return 0;
} /* woods */
