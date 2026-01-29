/*
 * /d/Gondor/pelargir/docks/lighthouse1.c
 *
 * Copyright (C) June 2, 1998 by Ron Miller (Tyr)
 *
 * Here begins a modification of the original code for the Pelargir 
 * lighthouse to update and convert it to use as a starting point 
 * for a quest.
 *
 * Revision History:
 *    6/28/99 - revised per Gnadnar's suggestions by Tyr
 *    4/2/01 - revised to make syntax less of a factor in the quest
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/*   PROTOTYPES    */
public void     create_gondor();
public void     init();
public string   exa_stairs(string arg);
public int      climb_stairs(string arg);

/* GLOBAL VARIABLES */
string *gFound = ({});

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("Ground floor of the Pelargir lighthouse");

    set_long(BSN("This is a lighthouse at the edge of the Pelargir "+
        "harbour. The floor here is cluttered with a huge pile of "+
        "broken bits of wood and planks. The debris partially covers "+
        "what was once a lovely mosaic on the floor. As it is, the "+
        "inhospitable atmosphere makes this an uncomfortable place "+
        "to be."));

    add_prop(ROOM_I_INSIDE,1);

    add_item( ({ "lighthouse", "structure" }) , BSN("This tall granite "+
        "tower was most likely constructed to warn passing ships of "+
        "some nearby danger."));

    add_item( ({ "granite", "pieces", "stone" }) , BSN("The rock used in the "+
        "construction this lighthouse appears to have been chosen more "+
        "for its hardness and durability than its aesthetic appeal."));

    add_item( ({ "rock", "stone" }) , BSN("The tower of the lighthouse is "+
        "built almost totally of stone."));

    add_item( ({ "tower", "granite tower" }) , BSN("A sturdy old structure, "+
        "this tower appears able to withstand even the fiercest of "+
        "storms."));

    add_item( ({ "ship", "ships", "danger", "wind", "winds", "storm", "storms",
        "edge", "pelargir", "pelargir harbour", "top", "harbour" }) , 
        BSN("With no windows here, it is quite impossible to see "+
        "anything outside the lighthouse."));

    add_item( ({ "window", "windows" }) , BSN("The tower is built with no "+
        "windows on this level."));

    add_item("floor", BSN("The floor of this room is made with fitted "+
        "blocks of the same granite used in the construction of the "+
        "rest of the tower structure."));

    add_item( ({ "ceiling", "shadows" }) , BSN("The ceiling here is shrouded "+
        "in shadows."));

    add_item( ({ "block", "blocks" }) , BSN("Large pieces of granite have "+
        "been shaped and smoothed to build the walls and floor of this "+
        "lighthouse."));

    add_item( ({ "wall", "walls" }) , BSN("The walls of this circular room "+
        "appear to be built with a local variety of granite."));

    add_item( ({ "room", "here" }) , BSN("This room is the first floor of "+
        "the lighthouse at the entrance of Pelargir harbour."));

    add_item( ({ "boards", "junk", "planks", "wood", "debris", "huge pile", 
        "pile", "litter", "remains", "bits", "remains" }) , BSN("Some "+
        "scaffolding and part of the supporting superstructure have "+
        "deteriorated and fallen on the floor here."));

    add_item( ({ "mosaic", "picture" }) , BSN("Though partially obscured by "+
        "the litter, the floor here is beautifully decorated with a "+
        "very detailed inlaid seascape."));

    add_item("seascape", BSN("In this nautical-themed mosaic picture, "+
        "a fleet of beautiful boats is riding the waves, each bearing "+
        "a large White Tree on its mainsail."));

    add_item("scaffolding", &exa_stairs("scaffolding"));

    add_item( ({ "waves", "wave", "water" }) , BSN("The boats in the mosaic "+
        "float serenely upon the water."));

    add_item( ({ "fleet", "boat", "boats" }) , BSN("The boats in the mosaic "+
        "are typical of those designed and built here in Gondor."));

    add_item( ({ "tree", "large tree", "large white tree", "white tree",
        "tall tree", "symbol", "symbol of gondor", "emblem",
        "emblem of gondor" }) , BSN("The most widely recognized symbol "+
        "of Gondor, a tall white tree, surrounded by seven stars is "+
        "set on a field of black."));

    add_item("stars", BSN("There are seven stars encircling a White "+
        "Tree in the emblem of Gondor."));

    add_item( ({ "field", "field of black", "background" }) , BSN("The "+
        "background of the emblem of Gondor is a simple field of solid "+
        "black."));

    add_item( ({ "sail", "sails", "mainsail" }) , BSN("The primary sail of "+
        "every boat in this mosaic is decorated with the White Tree of "+
        "Gondor."));

    add_item("superstructure", BSN("Though built of stone, the inside "+
        "of this tower is braced with massive timbers to help it "+
        "withstand the buffeting winds of the strongest storm."));

    add_item( ({ "timber", "timbers" }) , BSN("Ancient trees were shaped and "+
        "crafted to brace the structure here against the most severe "+
        "storms."));

    add_item( ({ "scaffold", "scaffolds" }) , BSN("The remains of a "+
        "temporary structure, probably used by some ancient workman in "+
        "his efforts to make repairs high up on the walls."));

    add_item( ({ "stair", "stairs", "staircase", "stairway", "access" }) , 
        &exa_stairs("stairs"));

    add_item("opening", &exa_stairs("opening"));

    add_cmd_item( ({"wood", "boards", "junk", "planks", "debris",
                    "pile", "pile of debris", "debris" }) ,
                  ({"search", "dig", "move" }), &exa_stairs("search"));

    add_exit((PELAR_DIR + "streets/beacon06"), "out", 0, 0);

    restore_object(MASTER);

} /* end create_gondor */

/*
 * Function name:   init
 * Description  :   add stair verbs
 */
public void
init()
{
    ::init();
    add_action(climb_stairs, "climb");
    add_action(climb_stairs, "ascend");
    add_action(climb_stairs, "up");
    add_action(climb_stairs, "u");
    add_action(climb_stairs, "squeeze");
} /* end init */

/*
 * Function name:   exa_stairs
 * Description  :   VBFC for scaffolding/stairs. Sets the property
 *                  that the player has actually found them, and
 *                  returns their description.
 * Arguments    :   string arg -- "scaffolding" or "stairs"
 * Returns      :   string -- the description
 */
public string
exa_stairs(string arg)
{
    if (member_array(TP->query_real_name(), gFound) == -1)
    {
        gFound += ({TP->query_real_name()});
        save_object(MASTER);
    }

    if (arg == "scaffolding")
    {
        return BSN("Someone apparently tried to make some structural "+
        "repairs here quite some time ago. The abandoned scaffolds "+
        "have fallen apart and partially block access to a stonework "+
        "stairway.");
    }

    if (arg == "search")
    {
         return BSN("Rummaging through "+
         "the debris reveals a small opening that allows access to a "+
         "spiral staircase which ascend to higher levels of the "+
         "lighthouse.");
    }

    if (arg == "opening")
    {
        return BSN("Luckily, some of the collapsed scaffold "+
        "caught enough of the falling debris to prevent it from "+
        "totally blocking access to the staircase up to the top of the "+
        "lighthouse. The opening is just barely large enough to "+
        "squeeze through.");
    }

    /* else arg is "stairs" */
    return BSN("A stonework stairway ascends in a spiral toward the "+
        "top of the tower. Though the access is blocked by the pile "+
        "of debris, there seems to be just enough of an opening to "+
        "squeeze through.");
} /* end exa_stairs */

/*
 * Function name:    climb_stairs
 * Description  :    handle attempts to climb the stairs -- only
 *                   succeeds if the player has exa'd the stairs
 *                   or the scaffolding.
 * Returns      :    1 on success, 0 on failure
 */
public int
climb_stairs(string arg)
{
    object    tp = TP;
    string    verb;

    if (member_array(tp->query_real_name(), gFound) == -1)
    {
        if (!tp->query_npc())
        {
            return 0;
        }
    }

    verb = QVB;
    if (verb != "u" && verb != "up")
    {
        if (!strlen(arg) || !parse_command(arg, ({}), 
          "[up] [through] [the] 'stair' / 'stairs' / 'stairway' / 'opening'"))
        {
            return 0;
        }
    }

    write("Squeezing through the opening in the debris, you ascend "+
      "the stairs to the second level of the lighthouse.\n");

    say(" disappears into the pile of debris.\n");


    tp->move_living("M", (PELAR_DIR + "docks/lighthouse2"));
    say(QCNAME(tp)+" arrives.\n");

    return 1;
} /* end climb_stairs */
