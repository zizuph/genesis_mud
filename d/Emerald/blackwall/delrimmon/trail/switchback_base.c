/*
 *  /d/Emerald/blackwall/delrimmon/path/switchback_base.c
 *
 *  This is the base of the southernmost arm of the
 *  Blackwall Mountains. Here, players can travel north
 *  into the Del Rimmon Area, which houses the Crystal
 *  Torque quest. There are switchbacks which lead up
 *  the cliff, and a forest to the south, where players
 *  can find the ferry back to Telberin.
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
 
inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include <stdproperties.h>

/* prototypes */
public void        create_del_rimmon();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("at the feet of the Blackwall Mountains");
    set_long("Tall and imposing, the Blackwall Mountains rise"
        + " to the north, their vast rocky slopes dominating the"
        + " northern landscape for as far as the eye can see. The"
        + " first walls of rock rise here, where a path of some"
        + " kind makes its way up the cliffs to the northeast. Just"
        + " to the east of the path, a mighty waterfall cascades"
        + " down the slopes, churning with froth at the base of"
        + " the cliffs where a river trails away through"
        + " a patch of forest which runs between the cliffs"
        + " and the northern shore of Lake Telberin to the south.\n");

    add_item( ({ "mountain", "mountains", "blackwall mountains",
                 "cliff", "cliffs", "wall", "walls", "wall of rock",
                 "walls of rock", "rock wall", "rock walls",
                 "slope", "rocky slope", "rock slope", "slopes",
                 "rocky slopes", "rock slopes", "first walls",
                 "first walls of rock", "steep cliff",
                 "steep cliffs", "landscape",
                 "north", "northeast", "cliffs to the northeast" }),
        "Here, the Blackwall Mountains send their southernmost"
      + " cliffs to crowd in on the lake, and surrounding area."
      + " Steep cliffs rise out of the ground, and trail off"
      + " for as far as the eye can see to the east and west."
      + " Just to the northeast, a trail makes its way up into"
      + " the slopes.\n");
    add_item( ({ "path", "trail", "road" }),
        "A path is visible, making its way up the difficult terrain"
      + " to the northeast. It appears to round a bend after a"
      + " short while, and is then lost from view.\n");
    add_item( ({ "bend", "corner" }),
        "The trail appears to round a corner after a short climb,"
      + " but little else is visible, as it is soon lost from"
      + " view.\n");
    add_item( ({ "ground", "down", "floor" }),
        "The ground here grows rocky, as the forest floor gives"
      + " way to the cliffs which rise to the north. A depression"
      + " in the ground runs from the forest toward the path"
      + " which leads up into the cliffs.\n");
    add_item( ({ "depression", "depression in the ground" }),
        "It appears as if this area once was the site of a very"
      + " well-travelled byway leading from the mountains to the"
      + " lake. A depression in the ground is still visible, where"
      + " once heavy-laden wagons or other such traffic may have"
      + " crossed.\n");
    add_item( ({ "forest", "patch of forest", "forest patch",
                 "wood", "woods", "tree", "trees" }),
        "A thick wood lies between these cliffs and the lake which"
      + " is a bit farther to the south. The sounds of various"
      + " birds and other animals occasionally sound over the"
      + " endless roar of the falls.\n");
    add_item( ({ "wind", "blowing wind", "breeze",
                 "steady breeze", "steady wind" }),
        "There is a steady breeze here, perhaps where the higher"
      + " air moves down along the slopes of the cliffs.\n");
    add_item( ({ "shore", "northern shore",
                 "northern shore of lake telberin",
                 "northern shore of the lake",
                 "lake", "water", "lake shore",
                 "lake telberin", "telberin lake" }),
        "The lake peers over and between the trees to the south,"
      + " glimmering with light.\n");
    add_item( ({ "falls", "waterfall", "rimmon falls", "cascade",
                 "mighty waterfall" }),
        "Cascading from hundreds of feet above, Rimmon Falls empty"
      + " the waters of the lake of Del Rimmon over the cliffs"
      + " of the Blackwall Mountains. The roar of the falls rises"
      + " as a near deafening tumult, spreading mist and water"
      + " vapor throughout the area.\n");
    add_item( ({ "mist", "vapor", "water vapor" }),
        "Mist from the waterfall wafts on the breeze throughout"
      + " along the rock walls, travelling down toward the forest"
      + " to the south.\n");
    add_item( ({ "stream", "river" }),
        "A river flows from the base of the waterfall toward"
      + " the trees, where it disappears to the south to eventually"
      + " feed into the waters of Lake Telberin.\n");

    add_cmd_item( ({ "mountain", "mountains", "blackwall mountains",
                 "cliff", "cliffs", "wall", "walls", "wall of rock",
                 "walls of rock", "rock wall", "rock walls",
                 "slope", "rocky slope", "rock slope", "slopes",
                 "rocky slopes", "rock slopes", "first walls",
                 "first walls of rock", "steep cliff",
                 "steep cliffs", "landscape",
                 "north", "northeast", "cliffs to the northeast" }),
                  ({ "climb" }),
        "You struggle a short distance up the sheer walls of"
      + " rock, and quickly decide that such a climb would prove"
      + " impossible, if not fatal.\n");

    add_exit(DELRIMMON_DIR + "trail/switchback1", "northeast");
    add_exit(DELRIMMON_DIR + "trail/forest_path", "south");

    set_no_exit_msg( ({ "northwest", "north" }),
        "The cliffs rise to block your passage in that direction.\n");
    set_no_exit_msg( ({ "west", "east" }),
        "You wander a bit along the cliffs, before returning to"
      + " where you were.\n");
    set_no_exit_msg( ({ "southeast", "southwest" }),
        "You trace the edges of the forest and soon return to where"
      + " you stood.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
} /* create_del_rimmon */



