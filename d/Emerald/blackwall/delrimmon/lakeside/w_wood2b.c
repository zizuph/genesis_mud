/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood2b.c
 *
 *  Debris from a violent rockslide to the southwest have cut away
 *  much of the foliage in this area, leaving a trail of ruin along
 *  this patch of forest on the western slopes rimming Del Rimmon
 *  in the Blackwall Mountains of Emerald.
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("west");

    set_extraline("A great swath has been carved into the woods here,"
      + " where rocky debris have swept aside bush and tree in what"
      + " appears to have been a very violent rockslide.");

    add_item( ({"swath", "trail of debris"}), BSN(
        "The destruction runs a ways to the northeast, where the final"
      + " objects of debris seem to have been strewn. From the look of"
      + " things, a massive rockslide has occurred to the southwest."));
    add_item( ({"debris", "rocky debris", "object", "objects",
                "objects of debris"}), BSN(
        "The debris on the ground seem to have erupted very violently"
      + " from the southwest. Large and small pieces of rock are mixed"
      + " with bits of torn and shredded foliage which must have been"
      + " rent asunder as the slide hit the woods."));
    add_item( ({"slide", "rockslide"}), BSN(
        "The objects in this area are merely the offshoots of what"
      + " must have been a very violent rockslide somewhere to the"
      + " southwest. Here within the tree cover, it is difficult to"
      + " see any details in that direction."));
    add_item( ({"southwest"}), BSN(
        "Looking southwest, you find it difficult to see anything"
      + " very clearly through the tree cover. There are obviously"
      + " cliffs in that direction, and the trail of debris seems"
      + " to have come from there."));
    add_item( ({"bush", "bushes", "bush and tree"}), BSN(
        "The foliage in this area has been ripped and cast aside by"
      + " the many tons of rock which seem to have spilled recently"
      + " through the forest from the southwest."));
    add_item( ({"rock", "piece of rock", "pieces of rock"}), BSN(
        "The pieces of rock are of all sizes, and lie strewn in a"
      + " northeasterly direction. They have cut through the foliage"
      + " in the area and lay in a great pile."));
    add_item( ({"large pieces of rock"}), BSN(
        "A few of the pieces of rock are at least as large as an"
      + " average human head, and look to weigh hundreds of pounds."));
    add_item( ({"small pieces of rock"}), BSN(
        "The smaller pieces of rock cover the ground here, filling"
      + " every nook and cranny of the forest bed."));
    add_item( ({"ground", "forest bed"}), BSN(
        "The ground here has been covered with debris which appear"
      + " to have shot through the area with great force."));
    add_item( ({"torn foliage", "shredded foliage",
                "torn and shredded foliage"}), BSN(
        "The foliage which is evident in the ruin has been ripped"
      + " from its beds to lie here amid the wreck."));

    add_cmd_item( ({"debris", "rocky debris", "rock", "pieces of rock",
                    "ground"}),
                  ({"search", "dig"}), BSN(
        "You dig around a bit in the debris, turning over rocks, and"
      + " examining the torn foliage, but find nothing of particular"
      + " interest."));
    add_cmd_item( ({"slide", "rockslide"}),
                  ({"search", "dig"}), BSN(
        "The main rockslide is yet southwest of here, and cannot be"
      + " explored in this area."));

    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3", "northeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1b","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff1", "southwest",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff2","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff3", "northwest",
             check_sitting,1,1);
} /* create_tree_room */
