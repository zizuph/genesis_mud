/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/sw_shore3.c
 *
 *  The lake shore extends diagonally along the southwestern
 *  edge of Del Rimmon here, travelling gradually under the
 *  shadow of Ael Rannath. A felled tree lies here - an interesting
 *  development, if not one terror of a red herring. ;-)
 *
 *  Copyright (c) September 1997 by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 *  Added fishing     : August 2021 (Gorboth)
 *
 *  XXX: Remember to remove the vision code from this room.
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeshore.c";

#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
int     Tree_Pushed = 0;

/* prototypes */
int push_tree(string str);

void   set_tree_pushed(int i) { Tree_Pushed = i; }
int    query_tree_pushed() { return Tree_Pushed; }

/*
 * Function name: create_lakeshore
 * Description  : allows us to create the room with area presets
 */
void
create_lakeshore()
{
    set_rope_tie( ({ "tree", "fallen tree", "branch" }) );

    set_loc(1);
    set_side("southwest");

    set_extraline("The pebble covered shore extends further along"
                + " the edge of Del Rimmon here, as the oval"
                + " lake curves gradually to the northwest and"
                + " southeast. A fallen tree extends from the"
                + " southwestern forest towards the lake here, its"
                + " green tufted branches splaying out across the"
                + " ground.");

    add_item( ({"wind", "winds", "breeze"}), BSN(
        "A steady breeze blows along the lake and its shores, yet"
      + " is certainly not strong enough to even bend the tops of"
      + " the trees."));
    add_item( ({"tree", "fallen tree"}), BSN(
        "This fir tree looks somewhat recently felled, as its"
      + " needles are still green, and the branches have not"
      + " dried and withered. Its tip almost touches the water of"
      + " the lake."));
    add_item( ({"tip", "tip of the tree"}), BSN(
        "The tip of the tree extends just short of the lake. You"
      + " detect no lack of health in the color of the uppermost"
      + " limbs."));
    add_item( ({"uppermost limb", "uppermost limbs"}), BSN(
        "There seems to be no reason that this tree should have"
      + " fallen. Here within the bowl of Del Rimmon, strong"
      + " winds are nearly unheard of."));
    add_item( ({"trunk", "tree trunk"}), BSN(
        "The trunk of the tree extends far to the southwest where"
      + " its base must lie amongst the trees there."));
    add_item( ({"branch", "branches", "green branches",
                "green tufted branches", "limb", "limbs"}), BSN(
        "The branches of this tree look strong and healthy."));
    add_item( ({"southwestern forest"}), BSN(
        "From the many trees covering the slopes to the southwest,"
      + " this singular trunk has fallen to earth."));
    add_item( ({"needle", "needles"}), BSN(
        "The needles of this fir tree are green and healthy looking."));
    add_item( ({"base", "base of the tree", "tree base",
                "base of the trunk"}), BSN(
        "The base of this tree is some distance to the southwest"
      + " among the many trees growing on the hillside there. You"
      + " cannot glimpse it from here."));

    add_cmd_item( ({"tree", "fallen tree", "tip", "tip of tree",
                    "uppermost limb", "uppermost limbs", "trunk",
                    "tree trunk", "branch", "branches", 
                    "green branches", "green tufted branches",
                    "base", "base of the tree", "tree base", 
                    "base of the trunk"}),
                  ({"search"}), BSN(
        "Carefully examining the tree, you can discover no signs"
      + " of malady or ill health. None of the branches are broken,"
      + " and there does not seem to be any fracturing in the trunk."
      + " Here along the lake, the winds are steady yet calm, making"
      + " this very puzzling indeed."));
    add_cmd_item( ({"tree", "fallen tree", "tree trunk"}),
                  ({"pull"}), BSN(
        "You pull a bit at the tree trunk, but do not seem to"
      + " have enough leverage to move it in such a way."));
    add_cmd_item( ({"tree", "tree trunk", "trunk", "on tree",
                    "on trunk", "on tree trunk"}),
                  ({"walk", "climb", "crawl"}), BSN(
        "You gingerly hop up onto the trunk of the fallen tree"
      + " and walk slowly along its length for a while. You"
      + " notice that doing so requires careful footing among"
      + " the branches, which splay out in all directions."));
    add_cmd_item( ({"branch", "branches", "limb", "limbs"}),
                  ({"break"}), BSN(
        "The branches of the tree are still quite green and"
      + " limber, making it difficult to snap them cleanly. Trying"
      + " only seems to bend them, ripping the wet and sappy"
      + " fibers, but not yielding anything useful."));


    add_exit(DELRIMMON_DIR + "lakeside/w_shore1","northwest");
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2","south",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2b","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_shore2","southeast");

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "north", "northeast", "east" }),
        "Unless you care to swim a great deal, you will need to travel"
      + " another direction.\n");
} /* create_lakeshore */

/*
 * Function name: push_tree
 * Description  : allows players to mess with the tree trunk. it can
 *                be pushed or pulled once from its original spot, and
 *                then sticks fast.
 * Arguments    : str (string) - what the player typed after the verb
 * Returns      : 1 - success, 0 - failure
 */
int
push_tree(string str)
{
    if (!strlen(str))
        NFN0(CAP(query_verb()) + " what?");

    if (str != "tree" && str != "tree trunk" && str != "trunk"
     && str != "fallen tree")
        NFN0("What do you wish to " + query_verb() + "?");

    if (Tree_Pushed)
    {
        write(BSN("You struggle for a while, straining with all"
                + " of your might to " + query_verb() + " the"
                + " trunk of the tree, but it seems to be lodged"
                + " well in place."));
        say(QCTNAME(TP) + " struggles in vain to " + query_verb()
                            + " the trunk of the tree forward. It"
                            + " seems to be lodged firmly in place.\n");

        return 1;
    }

    write(BSN("Struggling mightily, you manage to " + query_verb()
            + " the trunk of the tree forward a few feet, where"
            + " it lodges firmly in the ground."));
    say(QCTNAME(TP) + " struggles mightily against the trunk"
                        + " of the fallen tree, and manages to"
                        + " slowly " + query_verb() + " it a few"
                        + " feet forward, where it lodges itself"
                        + " firmly in the ground.\n");

    set_tree_pushed(1);
    return 1;
} /* push_tree */

/*
 * Function name: drag_tree
 * Description  : allows players to try to drag the tree in a direction
 * Arguments    : str (string) - what the player typed after the verb
 * Returns      : 1 - successful attempt, 0 - failure
 */
int
drag_tree(string str)
{
    if (!strlen(str))
        NFN0("Drag what?");

    if (str == "tree")
        NFN0("Which direction do you wish to drag it?");

    if (str != "tree north" && str != "tree south"
     && str != "tree west" && str != "tree east"
     && str != "tree southwest" && str != "tree southeast"
     && str != "tree northwest" && str != "tree southeast")
        NFN0("What do you wish to drag?");

    write("You attempt to drag the tree forward, but quickly discover"
        + " that its weight is far far too great for such an"
        + " endeavor.\n");
    say(QCTNAME(TP) + " attempts to drag the tree forward,"
                    + " but is foiled by the immense weight of"
                    + " the trunk.\n");

    return 1;
} /* drag_tree */

/*
 * Function name: init
 * Description  : add actions to the player
 */
void
init()
{
    ::init();

    add_action(drag_tree, "drag");
    add_action(push_tree, "push");
    add_action(push_tree, "move");
    add_action(push_tree, "roll");
} /* init */

/*
 * Function name: reset_room
 * Description  : reset the status of the tree so others can mess
 *                with it later this reboot
 */
void
reset_room()
{
    set_tree_pushed(0);
} /* reset_room */
