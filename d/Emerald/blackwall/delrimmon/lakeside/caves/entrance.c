/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/entrance.c
 *
 *  This is the entrance to a natural cavern which was expanded further
 *  in by Formandil's troops.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: July 2001
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void           create_del_rimmon();

/*
 * Function name:    create_del_rimmon
 * Description  :    set up the room
 */
public void
create_del_rimmon()
{
    set_short("a cave entrance in the cliffs on the western bank of"
            + " Del Rimmon");
    set_long("A narrow finger of light extends into this natural"
           + " cavern from a crack in the eastern rock walls. All around"
           + " and above, rough walls of stone rise and gradually widen"
           + " as they run to the west, where the cave appears to open"
           + " into a larger chamber.\n");

    add_item( ({"finger", "narrow finger", "finger of sunlight",
                "finger of moonlight", "sunlight", "moonlight",
                "narrow finger of sunlight",
                "narrow finger of moonlight"}), BSN(
        "The outside light filters in through the gap in the rock"
      + " walls to the east. In this dark cave, the light appears"
      + " almost blindingly intense."));
    add_item( ({"point", "above"}), BSN(
        "High above, the walls of the cave draw completely together,"
      + " closing completely in the shadows there."));
    add_item( ({"outside light"}), BSN(
        "The light from outside appears very bright, and obscured"
      + " any details as to what is beyond."));
    add_item( ({"cavern", "natural cavern", "cave", "here", "area",
                "natural cave"}), BSN(
        "This cavern appears to have been formed naturally, taking"
      + " on the shape of a deep crack in the cliffside which widens"
      + " to the west. The rock walls close in somewhat narrowly here."));
    add_item( ({"crack", "deep crack",
                "deep crack in the cliffside",
                "crack in the eastern rock walls"}), BSN(
        "This cavern, which appears to extend further to the west,"
      + " seems to be little more than a widening crack in the"
      + " cliffside."));
    add_item( ({"eastern rock walls", "eastern cliffside",
                "cliffside"}), BSN(
        "The cliffside to the east is broken by the entrance to this"
      + " cavern, where a finger of light extends into the shadows."));
    add_item( ({"shadow", "shadows"}), BSN(
        "Shadows lay heavily in this cavern, where natural light"
      + " is not present aside from that which issues in from the"
      + " entrance to the east."));
    add_item( ({"entrance", "entrance to the east"}), BSN(
        "The entrance is somewhat narrow, and allows a finger of"
      + " light to filter into this cavern."));
    add_item( ({"natural light"}), BSN(
        "The only natural light in this cavern comes from the entrance"
      + " to the east, where the outside can be barely glimpsed."));
    add_item( ({"outside"}), BSN(
        "The light from the entrance is too blinding to allow for"
      + " many details to be viewed."));
    add_item( ({"rock walls", "walls", "wall", "rock wall",
                "rough wall", "rough walls", "walls of stone",
                "stone wall", "stone walls", "rough walls of stone",
                "rough wall of stone", "cave wall", "cave walls",
                "walls of the cavern"}), BSN(
        "The walls of this cavern are rough and close in narrowly"
      + " towards the entrance to the east. They rise to some dark"
      + " crest above, and gradually widen to the west, where it"
      + " appears as if there is a larger chamber in that direction."));
    add_item( ({"crest", "dark crest", "dark crest above",
                "crest above", "ceiling", "roof", "cave roof"}), BSN(
        "The rough walls of the cave extend above, where they gradually"
      + " narrow to a point at which they seem to come together."));
    add_item( ({"sky", "sun", "moon"}), BSN(
        "The sky is not visible inside this cave in the cliffside"));
    add_item( ({"chamber", "larger chamber", "chamber to the west",
                "western chamber"}), BSN(
        "To the west, it appears as if the cave continues into the"
      + " darkness, widening into a much larger chamber."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG, "A dark cave, lit only by a narrow"
                             + " finger of light to the east.\n");
    add_prop(ROOM_S_DARK_MSG, "The narrow finger of light to the east"
                            + " is the only thing visible in this dark"
                            + " cave. You cannot");
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/w_cliff5", "east");
    add_exit(DELRIMMON_DIR + "lakeside/caves/large_room", "west");

    set_no_exit_msg( ({ "northwest", "north", "northeast",
                        "southwest", "south", "southeast" }),
        "The cave walls rise to meet you in that direction.\n");
} /* create_del_rimmon */
