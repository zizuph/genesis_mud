/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_cliff4.c
 *
 *  The cliffs which surround the lake of Del Rimmon in the Blackwall Mountains
 *  of Emerald round a slight bend here at the northwestern region of
 *  the western shores. An old log and some ants keep the place
 *  company.
 * 
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("northwest");

    set_extraline("The cliffs round a bend here, running"
                + " in a straight line to the east, and tracing a"
                + " long curve to the southwest. A very old and"
                + " decayed tree trunk lies against the cliff base"
                + " here.");

    add_item( ({"ground", "cliff base", "base of the cliff"}), BSN(
        "The ground at the base of the cliff here is interrupted by"
      + " a thin trail of ants which marches into the woods to the south."
      + " An old decayed log rests at the edge of the cliff."));
    add_item( ({"edge", "edge of the cliff", "cliff edge"}), BSN(
        "The edge of the cliff rises high into the air above. At its"
      + " base rests an old and decayed tree trunk."));
    add_item( ({"bend", "turning point"}), BSN(
        "The cliffs which rise on all sides of the lake round a bend"
      + " here, which marks the turning point in the straight line"
      + " the cliffs seem to have followed from the east."));
    add_item( ({"straight line", "line", "straight line to the east"}),
    BSN("The cliffs run in nearly a straight line to the east, where"
      + " it appears as if they turn directly south in the distance"
      + " in that direction."));
    add_item( ({"curve", "long curve"}), BSN(
        "The cliffs trace the contours of the lake as they extend to"
      + " the southwest from this point."));
    add_item( ({"contour", "contour of the lake", "contours",
                "contours of the lake"}), BSN(
        "The lake curves in a gradual arc here on the west side of"
      + " Del Rimmon. The cliffs trace that arc to the south."));
    add_item( ({"arc", "arc of the lake"}), BSN(
        "The arc of the contours of the lake is long and gradual."));
    add_item( ({"trunk", "tree trunk", "old trunk", "old tree trunk",
                "decayed trunk", "decayed tree trunk", 
                "old and decayed tree trunk"}), BSN(
        "What appears to have once been a tall and sturdy tree lies"
      + " on its side here at the base of the cliffs. Much rot and"
      + " decay have taken place upon its surface, where insects and"
      + " moss are visible working their natural ways."));
    add_item( ({"rot", "decay", "rot and decay"}), BSN(
        "The decay which the old tree trunk has undergone would suggest"
      + " that it has lain here for many, perhaps hundreds of years."));
    add_item( ({"moss"}), BSN(
        "Pale green moss clings to the decayed bark of the tree trunk."));
    add_item( ({"bark", "decayed bark"}), BSN(
        "Tiny ants crawl to and from from many holes in the bark of the"
      + " old tree."));
    add_item( ({"hole", "holes", "many holes"}), BSN(
        "The holes riddle the bark of the tree, and many hundreds of ants"
      + " are visible crawling in and out of them."));
    add_item( ({"ant", "ants", "many ants", "hundreds of ants"}), BSN(
        "The ants swarm all over the old tree trunk, crawling in and out"
      + " of holes in the bark. A long and thin trail of their tiny"
      + " bodies leads into the forest to the south."));
    add_item( ({"insect", "insects"}), BSN(
        "Closer inspection of the insects along the old tree reveals"
      + " that they are in fact ants."));
    add_item( ({"trail", "long trail", "thin trail",
                "long and thin trail", "ant trail", "trail of ants",
                "thin trail of ants", "long and thin trail of ants"}),
    BSN("The trail of ants winds its way to the south, where it"
      + " appears to enter the forest in that direction."));
    add_item( ({"body", "bodies", "tiny bodies", "ant bodies"}), BSN(
        "The ants have bodies which are red at the head, and black"
      + " in the region of the abdomen and thorax."));
    add_item( ({"head", "ant head", "red head"}), BSN(
        "The heads of the tiny ants are indeed red. Mean-looking red!"));
    add_item( ({"thorax", "abdomen"}), BSN(
        "The abdomen and thorax regions of the tiny ant bodies are"
      + " a shiny, solid black colour."));

    add_cmd_item( ({"ants", "ant", "on ants", "on ant"}),
                  ({"step", "squash", "stomp", "smash", "crush"}), BSN(
        "You plant your foot heavily on the surface of the old tree,"
      + " attempting to crush the many ants which crawl on its surface."
      + " While you seem to have succeeded in killing one or two of"
      + " the tiny creatures, the rest appear undaunted, and continue"
      + " with their ceaseless labour."));
    add_cmd_item( ({"ant", "ants"}),
                  ({"kill"}), BSN(
        "How do you propose to kill the ants?"));
    add_cmd_item( ({"train", "on trail", "long trail", "on long trail",
                    "thin trail", "on thin trail", "trail of ants",
                    "on trail of ants", "ant trail", "on ant trail",
                    "long and thin trail", "on long and thin trail"}),
                   ({"step", "stomp", "squash", "smash", "crush"}), BSN(
        "You stomp agressively on the trail of ants. Where your foot"
      + " lands, a momentary frenzy of activity breaks out among the"
      + " tiny creatures, only to soon die down again. The ants continue"
      + " their labours."));
    add_delay_cmd_item( ({ "trunk", "tree trunk", "old trunk",
                           "old tree trunk", "decayed trunk",
                           "decayed tree trunk",
                           "old and decayed tree trunk"}),
                        "search",
                        "searching the trunk",
                        10,
                        "You begin searching the old and decayed tree"
                      + " trunk.\n",
                        "Aside from hundreds of ants, you find nothing"
                      + " interesting about the old trunk other than its"
                      + " seemingly great age.\n");

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff5","east");
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3","southeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3b","south",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff3","southwest");

    set_no_exit_msg( ({ "west", "northwest", "north", "northeast" }),
        "The cliff walls block any movement in that direction.\n");
} /* create_cliff_room */

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
