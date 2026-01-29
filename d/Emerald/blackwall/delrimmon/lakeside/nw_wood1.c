/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_wood1.c
 *
 *  The forest which surrounds the lake of Del Rimmon in the Blackwall
 *  Mountains winds to the northwest of the lake here. A little row
 *  of saplings grow from a nursery log amid the tree trunks.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
void           create_tree_room();


/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("northwest");

    set_extraline("Rays of light filter gently through the quietly"
                + " swaying branches overhead to illuminate the forest"
                + " floor. In the midst of this wooded area a row of"
                + " young and eager saplings rises from the aged husk of"
                + " a mossy tree trunk which has fallen to earth.");

    add_item( ({"ray", "rays", "light", "sunlight", "moonlight",
                "ray of sunlight", "rays of sunlight",
                "ray of moonlight", "rays of moonlight",
                "ray of light", "rays of light"}), BSN(
        "Rays of light usher in from cracks in the swaying branches"
      + " overhead. They illumine the forest floor here, where an"
      + " old trunk appears to be the father of many young"
      + " saplings."));
    add_item( ({"crack in the branches", "cracks in the branches"}),
    BSN("The branches overhead sway softly in some unfelt breeze,"
      + " allowing light to seep in through the cracks."));
    add_item( ({"breeze", "unfelt breeze"}), BSN(
        "The swaying of the branches is the only testimony to the"
      + " presence of a breeze running through the woods."));
    add_item( ({"floor", "forest floor", "ground", "earth"}), BSN(
        "The ground here is covered with moss and other undergrowth."
      + " An old tree trunk lies amid the trees of the forest, hosting"
      + " a row of young saplings which grow on its decayed husk."));
    add_item( ({"fungus"}), BSN(
        "Fungus clusters to various areas of the decayed tree trunk,"
      + " interspersed with the moss which grows upon its husk."));
    add_item( ({"aged husk", "trunk", "mossy trunk", "tree trunk",
                "mossy tree trunk", "husk", "decayed husk",
                "fallen tree", "old trunk", "old tree trunk"}), BSN(
        "An old decayed tree trunk spans the forest floor here,"
      + " covered by thick moss and fungus. It appears to be a"
      + " nursery log, as many young and eager saplings spring"
      + " forth from the top of its decayed husk."));
    add_item( ({"thick moss"}), BSN(
        "The moss on the decayed tree trunk grows around the"
      + " young saplings which rise from its decayed husk."));
    add_item( ({"sapling", "saplings", "many young saplings",
                "young saplings", "eager saplings",
                "young sapling", "eager sapling",
                "young and eager saplings"}), BSN(
        "The saplings are infant versions of the trees which grow"
      + " in these woods. Rather than growing from the ground, they"
      + " have taken root in the trunk of a fallen tree, where the"
      + " process of decay has provided a rich bed of nutrients."));
    add_item( ({"nursery log", "log", "process of decay", "decay",
                "bed", "rich bed", "rich bed of nutrients",
                "nutrients"}), BSN(
        "The process of decay in the fallen tree have made it the"
      + " perfect place for these young saplings to grow."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2b","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2", "northeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore1","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore5","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5", "southwest",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1b","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff2", "northwest",
             check_sitting, 1, 1);

    set_no_exit_msg( ({ "southeast" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");
} /* create_tree_room */
