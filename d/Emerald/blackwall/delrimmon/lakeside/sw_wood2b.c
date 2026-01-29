/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/sw_wood2b.c
 *
 *  The forest here along low slopes of the Blackwall Mountains bordering
 *  Del Rimmon is quiet and undisturbed for the most part in this
 *  south western quarter. This room, however, bears a grim
 *  testimony to the presence of some evil activity in the area.
 *
 *  Copyright (c) November 1997, by Cooper Sherry (Gorboth)
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
    set_side("southwest");

    set_extraline("The gradual slope of the hillside becomes more"
                + " pronounced to the west and south, where glimpses"
                + " can be had of stark cliff faces peering through"
                + " the trees. A tree has been felled here, as"
                + " evidenced by a hewn stump and tree trunk splayed"
                + " on the ground.");

    add_item( ({"slope", "gradual slope", "slope of the hillside"}),
        BSN("The slope of the hillside grows steadily more vertical"
          + " to the south and west, where cliff faces can be seen"
          + " peering through the tree trunks."));
    add_item( ({"tree", "trunk", "tree trunk", "felled tree"}),
        BSN("This tree looks to have been cut down in its prime."
          + " Rough gouges are visible at its base, where it was"
          + " evidently hacked with some sort of an axe."));
    add_item( ({"base", "tree base"}), BSN(
        "The many rings at the tree base reveal that this was indeed"
      + " a tree of noble age. The hack marks which proceed to nearly"
      + " the center of the trunk appear to have come from different"
      + " directions, and seem as rather crude strokes. A large"
      + " section of bark and wood have been peeled away where the"
      + " tree evidently pivoted from its roots and was torn"
      + " as it hit the ground."));
    add_item( ({"ring", "rings", "tree ring", "tree rings"}), BSN(
        "There are several hundred rings at least in this tree."
      + " A few show evidence that the great pine had withstood"
      + " a fire or burning."));
    add_item( ({"marks", "hack marks", "gouges", "rough gouges",
                "mark", "hack mark", "gouge", "rough gouge"}), BSN(
        "The hack marks are crude and seem to have come from more"
      + " than one direction. Whoever is responsible for the felling"
      + " of this great tree seems to have cut the tree down for"
      + " no better reason than the love of destruction."));
    add_item( ({"stump", "hewn stump", "roots", "root", "tree stump"}),
        BSN("The stump of the tree is littered with bits of wood which"
      + " were shorn from the shattered trunk as it was chopped"
      + " to earth. Half of the perimeter of the tree is torn with"
      + " the cruel gouges, to be interrupted by a large section"
      + " of wood and bark which stands erect from the stump."));
    add_item( ({"section of wood", "section of bark",
                "section of wood and bark", "bark",
                "large section of wood and bark", "section"}), BSN(
        "A large section of wood and bark stands erect from the"
      + " tree stump as a long sliver. It would seem to be a remnant"
      + " of the great trunk which, when hacked partway through,"
      + " must have been pushed or forced over, to pivot away from"
      + " its base and rip off from this point."));
    add_item( ({"bits", "bits of wood", "bit", "bit of wood"}), BSN(
        "The bits of wood which lie scattered about the trunk and"
      + " stump of the tree do not appear older than two days. Their"
      + " colour is yet that of freshly hewn timber."));
    add_item( ({"ground"}), BSN(
        "The mosses and undergrowth along the ground here have been"
      + " sprinkled with small chunks of wood pulp and bark. A large"
      + " tree trunk lies along the ground, running northeast away from"
      + " its carven base."));
    add_item( ({"chunk", "chunks", "chunks of wood", "pulp",
                "chunks of wood pulp", "chunk of wood", "wood pulp",
                "chunk of wood pulp"}), BSN(
        "Pieces of the hewn stump lie scattered amongst the undergrowth"
      + " here, testimony to the chopping down of a nearby tree."));

    add_cmd_item( ({"trunk", "tree trunk", "felled tree"}),
                  ({"move", "lift", "pull", "push", "roll"}), BSN(
        "At this end, the trunk is thick and heavy - far too massive to"
      + " be moved much in any way you could provide."));
    add_cmd_item( ({"stump", "trunk", "tree stump", "tree trunk",
                    "felled tree", }),
                  ({"search"}), BSN(
        "There have been no attempts to alter the tree other than"
      + " chopping it down. It would seem that this act was one of"
      + " thoughtless destruction, and for no useful purpose at all."));

    add_exit(DELRIMMON_DIR+"lakeside/sw_wood3","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_shore3", "northeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_wood2","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff2", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_cliff3","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_cliff4","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3b", "northwest",
             check_sitting,1,1);

    set_no_exit_msg( ({ "southwest" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");
} /* create_tree_room */
