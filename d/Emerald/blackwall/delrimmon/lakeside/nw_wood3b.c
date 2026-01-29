/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_wood3b.c
 *
 *  This bit of forest lies in the northwestern region of the slopes
 *  which surround Del Rimmon in the Blackwall Mountains. Ants happily
 *  occupy this territory.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
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
    set_side("northwest");

    set_extraline("The forest grows somewhat densely here, and the"
                + " canopy of branches overhead has cast many shadows"
                + " about the area. A tall mound of some sort rises"
                + " from the ground beside a tree stump which rests"
                + " a few feet away.");

    add_item( ({"light", "light from the sky"}), BSN(
        "The occasional swaying of a branch overhead allows only"
      + " a very small amount of light to penetrate through the"
      + " canopy overhead."));
    add_item( ({"canopy", "canopy of branches"}), BSN(
        "The canopy of branches overhead grows very tightly, and"
      + " prevents much of the light from the sky above from"
      + " penetrating to the forest floor."));
    add_item( ({"ground", "floor", "forest floor"}), BSN(
        "The ground here swarms with ants, which make their way"
      + " to a tall mound which rises beside a tree stump here."));
    add_item( ({"shadow", "shadows"}), BSN(
        "Shadows are all about in this rather dense section of the"
      + " forest, deepened by the canopy of branches overhead which"
      + " clusters tightly together."));
    add_item( ({"area"}), BSN(
        "This bit of forest is dense, and crowded with shadow."));
    add_item( ({"mound", "tall mound"}), BSN(
        "Upon closer inspection, it becomes apparent that the mound"
      + " is in fact inhabited by many thousands of ants, which crawl"
      + " restlessly upon its surface."));
    add_item( ({"surface", "surface of the mound",
                "surface of the anthill"}), BSN(
        "The surface of the ant hill is teaming with ants."));
    add_item( ({"ant hill"}), BSN(
        "The mound which rests beside a tree stump on the ground here"
      + " does indeed appear to be an ant hill, crawling with its"
      + " countless inhabitants."));
    add_item( ({"inhabitant", "inhabitants", "countless inhabitants"}),
    BSN("The anthill is certainly inhabited! Countless ants swarm in a"
      + " weaving pattern over the entire surface of the mound."));
    add_item( ({"surface of the mound"}), BSN(
        "The surface of the mound is covered by nearly countless"
      + " ants, busy at their many labours."));
    add_item( ({"pattern", "weaving pattern"}), BSN(
        "Staring at the pattern the ants weave, you find yourself"
      + " growing a bit itchy."));
    add_item( ({"ant", "ants"}), BSN(
        "The ants have black bodies and red heads, and swarm all over"
      + " a tall mound which rises from the ground near to here. They"
      + " are skitting along the ground in a neat trail here, and can"
      + " be seen crawling individually over almost everything in the"
      + " immediate area."));
    add_item( ({"bodies", "ant bodies", "black bodies"}), BSN(
        "The thorax and abdomen regions of the ants are a dark and"
      + " shiny black colour."));
    add_item( ({"head", "heads", "red heads", "red head"}), BSN(
        "The heads of the ants which crawl along the ground are red,"
      + " and appear to have long pincers extending from them."));
    add_item( ({"pincer", "pincers", "long pincer", "long pincers"}),
    BSN("The pincers look like they could deliver a nasty bite!"));
    add_item( ({"trail", "trail of ants", "ant trail",
                "neat trail"}), BSN(
        "The trail of ants is very specific, and runs along the"
      + " ground leading to and from the tall mound which rises"
      + " next to a nearby stump."));
    add_item( ({"stump", "nearby stump", "tree stump",
                "nearby tree stump"}), BSN(
        "The stump is positively crawling with ants, which run up"
      + " and down its sides, on their way to and from a tall"
      + " mound which grows next to it."));
    add_item( ({"sides", "sides of the stump"}), BSN(
        "The sides of the stump are covered with ants on their way"
      + " to and from a nearby mound."));

    add_cmd_item( ({"ant", "ants"}),
              ({"kill"}), BSN(
        "There are literally thousands of ants here. How do you propose"
      + " to kill them?"));
    add_cmd_item( ({"ant", "ants", "on ant", "on ants"}), 
              ({"squash", "step", "smash", "stomp"}), BSN(
        "You stomp visciously on the ants, crushing a few of them. A"
      + " swarm of anger takes the remaining ants for a few moments,"
      + " to eventually die down again. The ants go on with their"
      + " business."));
    add_cmd_item( ({"ant hill", "anthill", "mound", "tall mound"}),
                  ({"search", "dig"}), BSN(
        "Ants swarm all over your hands as you attempt to search the"
      + " mound. Instinctively, you dance around, swatting them"
      + " sharply from your hands and forearms."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff4","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff5", "northeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore2", "southeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2b", "southwest",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff3","west",check_sitting,1,1);

    set_no_exit_msg( ({ "northwest" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");
} /* create_tree_room */
