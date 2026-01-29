/*
/*  /d/Emerald/blackwall/delrimmon/lakeside/w_cliff1.c
 *
 *  Here, along the western cliffs just west southwest of the center
 *  of Del Rimmon in the Blackwall Mountains, a massive rockslide has
 *  occurred, sending a huge wall of rubble sliding into the area.
 *  There is quite a lot to look at here. :)
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public int     climb_debris();
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("west");

    set_extraline("Many tons of mud and stone lie splayed out from"
                + " the edge of the cliffs here, where it appears"
                + " as if a massive rockslide of some sort has"
                + " occurred recently.");

    add_item( ({"mud", "tons of mud",
                "stone", "stones", "tons of stone",
                "mud and stone", "tons of mud and stone"}), BSN(
        "The debris from the cliff run in a northeastern direction"
      + " from here, piled in a crumbled mound which is at least"
      + " four feet high in most places."));
    add_item( ({"apparatus"}), BSN(
        "Whatever these beams once comprised, they are nothing but"
      + " a broken heap now."));
    add_item( ({"debris", "pile", "mound", "crumbled mound",
                "debris from the cliff", "rockslide",
                "massive rockslide"}), BSN(
        "The wreck from the rockslide seems mostly composed of"
      + " fragments of stone from the cliff face which have been"
      + " rent into vast and shattered boulders, or crumbled into"
      + " tiny smithereens. There also appears to be some"
      + " wood splinters amid the ruins."));
    add_item( ({"fragments", "fragments of stone",
                "shattered fragments", "shattered fragments of stone",
                "vast fragments", "boulder", "boulders",
                "vast boulders", "shattered boulders"}), BSN(
        "Boulders lie heaped in jagged piles amid the ruin of the"
      + " rockslide. Their crushing weight has in many places"
      + " thrust the feet of the stones deep beneath the surface"
      + " of the ground."));
    add_item( ({"smithereens", "tiny smithereens", "smithereen"}),
    BSN("Dust and tiny pebbles from the rockslide cover everything"
      + " here, carpeting the area with a layer of chalky grit."));
    add_item( ({"wood", "splinters", "wood splinters"}), BSN(
        "The wooden splinters which lie amid the wreck of the"
      + " rockslide were clearly not formed naturally. They appear"
      + " to be crushed and ruined beams which were at one time"
      + " assembled to form some very large apparatus. Now they"
      + " are no more than a broken heap."));
    add_item( ({"beam", "beams", "crushed beam", "crushed beams",
                "ruined beam", "ruined beams", "broken beams",
                "crushed and ruined beam", "crushed and ruined beams",
                "heap", "broken heap"}), BSN(
        "It is unclear what this mass of shorn and broken beams"
      + " was once built to be. Splintered beams and wooden"
      + " planks are heaped together in a tangled mess. One of"
      + " the beams has an odd shape to it."));
    add_item( ({"odd beam", "odd shape", "beam with odd shape",
                "beam with odd shape to it"}), BSN(
        "This beam is far sturdier than the others, and has somehow"
      + " avoided the destruction which the rest of its apparatus"
      + " has suffered. A cupped metal basin is fixed to one end"
      + " of the beam."));
    add_item( ({"others", "other beams"}), BSN(
        "The other beams are both less thick, and comprised of softer"
      + " wood than the beam with the odd shape to it."));
    add_item( ({"dust", "grit", "layer of chalky grit",
                "chakly grit"}), BSN(
        "The dust seems to have settled on nearly everything in this"
      + " immediate area."));
    add_item( ({"basin", "metal basin", "cupped basin",
                "cupped metal basin"}), BSN(
        "The basin attached to the sturdy looking beam is"
      + " cupped like a massive spoon.") );
    add_item( ({"plank", "planks",
                "wooden plank", "wooden planks"}), BSN(
        "The planks of wood appear to be quite old. They are dried"
      + " and brittle, and in most cases have been ripped to pieces"
      + " or folded over upon themselves in a splintered heap."));
    add_item( ({"ground", "down"}), BSN(
        "The ground here is completely covered by the remnants of"
      + " a major rockslide. Huge boulders are scattered everywhere,"
      + " piled in a long wall of debris which stretches into the"
      + " forest to the northeast."));
    add_item( ({"catapult", "catapults"}), BSN(
        "Perhaps this ruined wreck was once a catapult, judging from"
      + " the shape of the cupped metal basin which is attached to"
      + " the end of one of the largest beams. Yet now all that"
      + " remains is ruin."));

    add_cmd_item( ({"rockslide", "wreck", "debris",
                    "pile", "debris from the cliff",
                    "massive rockslide", }),
                  ({"search", "dig"}), BSN(
        "Digging around in the debris of the rockslide, you"
      + " notice nothing unusual, aside from some broken beams"
      + " of wood which lie in the wreckage near to the cliff.") );
    add_cmd_item( ({"beam", "beams", "heap", "broken heap"}),
                  ({"search", "dig"}), BSN(
        "The beams of wood seem loosely connected, and yet it is"
      + " not clear what apparatus this mess once comprised. You"
      + " notice one particularly odd shaped beam amid the mass.") );
    add_cmd_item( ({"beam", "beams", "heap", "broken heap"}),
                  ({"get"}), BSN(
        "The beams are either covered with heavy rubble, or firmly"
      + " attached to one another. They cannot be moved."));
    add_cmd_item( ({"basin", "cupped basin"}),
                  ({"get"}), BSN(
        "The basin is firmly attached to the sturdy beam which"
      + " bears it. You see no way in which it might be removed."));

    add_exit(DELRIMMON_DIR + "lakeside/w_cliff2","north",climb_debris,4);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2b","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1b","east",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff5","southeast");

    set_no_exit_msg( ({ "south", "southwest", "west", "northwest" }),
        "The cliffs rise to defy your movement.\n");
} /* create_cliff_room */

/*
 *  Function name: climb_debris
 *  Description  : shows the player that they are climbing over
 *                 the rockslide debris. 
 *  Arguments    : none
 *  Returns      : 0
 */
public int climb_debris()
{
    write(BSN("You climb over the debris from the rockslide and"
            + " travel north."));

    return 0;
} /* climb_debris */

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
