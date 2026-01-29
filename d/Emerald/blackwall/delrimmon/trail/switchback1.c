/*
 *  /d/Emerald/blackwall/delrimmon/trail/switchback1.c
 *
 *  This is the bottom of the switchback trail which leads up
 *  to Del Rimmon.
 *
 *  Copyright (c) November 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>      /* for QCTNAME, etc */
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */

/* prototypes */
public void        create_del_rimmon();
public void        add_switchback_items();


/*
 * Function name:       create_del_rimmon
 * Description :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_cliffs");
    set_short("on some switchbacks in the Blackwall Mountains");

    set_long("A narrow trail zig-zags up the cliffs here,"
      + " making its gradual way towards the top of this rise. To"
      + " the southwest, the trail slopes down to the forest at the"
      + " foot of these cliffs which travels away to the south to"
      + " meet with the waters of the Telberin River. Round a sharp"
      + " switchback, the trail continues up to the northwest."
      + " Spray from the waterfall just to the east fills the"
      + " air, and the sound is deafening.\n");

    add_item( ({ "foot", "foot of these cliffs", "foot of the cliffs",
                 "base", "base of the cliffs", "cliff base" }),
        "The base of the cliffs lies down the trail to the southwest. It"
      + " appears as if the trail curves to the south there, running"
      + " along to disappear into the trees.\n");

    add_switchback_items();
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_exit(DELRIMMON_DIR + "trail/switchback_base", "southwest");
    add_exit(DELRIMMON_DIR + "trail/switchback2", "northwest",
             0, 10, 0);

    set_no_exit_msg( ({ "north", "northeast", "west" }),
        "The cliffs block your movement in that direction.\n");
    set_no_exit_msg( ({ "east", "southeast", "south" }),
        "The fall from the dropoff in that direction would"
      + " surely be your last.\n");
    set_no_exit_msg( ({ "down" }),
        "You can travel down the switchbacks to the southwest.\n");
    set_no_exit_msg( ({ "up" }),
        "You can travel up the switchbacks to the northwest.\n");
} /* create_del_rimmon */


/*
 * Function name:        add_switchback_items
 * Description  :        add_items which are constant for
 *                       the switchback rooms
 */
public void
add_switchback_items()
{
    try_item( ({ "trail", "narrow trail", "path", "narrow path",
                 "switchback", "switchbacks", "switch back",
                 "switch backs" }),
        "The path you are on makes its way up the cliffs via"
      + " switchbacks which allow for gradual altitude gain at"
      + " a manageable grade. The path is narrow, and the drop"
      + " to the south is rather sheer.\n");
    try_item( ({ "drop", "dropoff", "south", "slope",
                 "steep slope" }),
        "To the south, the path falls away as a very steep slope"
      + " veers to the ground far below.\n");
    try_item( ({ "below", "ground below", "ground far below" }),
        "The ground is a long way down from here, and a fall would"
      + " almost certainly prove fatal.\n");
    try_item( ({ "cliff", "cliffs", "rise" }),
        "The switchbacks make their way up a tall rise here,"
      + " moving gradually up the face of a rather sheer run of"
      + " cliffs.\n");
    try_item( ({ "forest", "wood", "woods", "trees", "tree" }),
        "A the base of the cliffs, a thick woods cluster between"
      + " rock and water. The trees extend a ways to the south"
      + " to eventually halt at the shores of the River"
      + " Telberin.\n");
    try_item( ({ "water", "river", "telberin river",
                 "river telberin" }),
        "The Telberin River runs from the base of the waterfall,"
      + " travelling southward to meet with Lake Telberin in the"
      + " far distance.\n");
    try_item( ({ "telberin lake", "lake telberin", "lake",
                 "waters" }),
        "Telberin lake is a great distance to the south. From here"
      + " it appears as only a glint of silver along the"
      + " horizon.\n");
    try_item( ({ "waterfall", "fall", "falls", "rimmon falls" }),
        "Rimmon Falls, the great waterfall of Emerald, pours its"
      + " waters over a giant sluice high above. The mist from"
      + " the falling waters fills the air here, and the sound"
      + " of the pounding spray is constant. These switchbacks"
      + " are just a ways to the west of the Falls themselves.\n");
    try_item( ({ "sluice", "giant sluice" }),
        "The sluice is high above, but you can still get a good"
      + " impression of the vast amounts of water which tumble"
      + " over its edge every second.\n");
    try_item( ({ "ground", "down", "floor" }),
        "The ground here is rough and somewhat uneven, even where"
      + " the switchbacks are well-worn. It appears as if this"
      + " trail has seen little use over the recent years.\n");
    try_item( ({ "up", "sky" }),
        "The sky above is blue and beautiful.\n");
    try_item( ({ "spray", "mist" }),
        "The air is thick with mist from Rimmon Falls which"
      + " loom just to the east.\n");
    try_item( ({ "mountains", "blackwall mountains", }),
        "This cliff is merely the southern exposure of the many"
      + " jagged rises which form the Blackwall Mountains. The"
      + " greater peaks are obscured from view here, though they"
      + " do lay spread out to the north for hundreds of miles.\n");

} /* add_switchback_items */

