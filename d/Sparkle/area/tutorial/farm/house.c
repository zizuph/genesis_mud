/*
 *  /d/Sparkle/area/tutorial/farm/house.c
 *
 *  This is the farmhouse north of Greenhollow. This is where the
 *  Farmer's wife gives out quests and rewards.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* global variables */
#define     TUTORIAL_CHAPTER        35       /* chapter for the sign */

/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public void        describe(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("in a simple farmhouse");
    set_long("You stand in a simple farmhouse. All around you are"
      + " the comforts of home. Light curtains blow with an easy"
      + " breeze that comes through an open window looking out on"
      + " the barnyard. Fuel is piled beside a wood stove which"
      + " stands in the kitchen. A door leads west back outside.\n\n");

    add_item( ({ "here", "area", "room", "house", "farmhouse",
                 "simple farmhouse" }), long);
    add_item( ({ "curtain", "curtains", "light curtain",
                 "light curtains", "breeze", "easy breeze",
                 "window", "barnyard", "yard", "open window",
                 "south", "south wall", "southern wall" }),
        "Breeze coming in from the yard blows the window's curtains"
      + " to and fro along the south wall.\n");
    add_item( ({ "west", "west wall", "western wall",
                 "door", "doorway" }),
        "The doorway in the west wall leads back out onto the"
      + " barnyard.\n");
    add_item( ({ "east", "east wall", "eastern wall", "kitchen" }),
        "The kitchen is in the eastern portion of the room. It looks"
      + " well-used.\n");
    add_item( ({ "north", "north wall", "northern wall", "stove",
                 "wood stove" }), &describe("stove"));
    add_item( ({ "broth", "pot", "large pot", "potion broth" }),
        &describe("broth"));
    add_item( ({ "floor", "rug", "heavy rug", "down", "ground" }),
        "A heavy rug covers most of the floor in here.\n");
    add_item( ({ "rafters", "rafter", "wooden rafter",
                 "wooden rafters", "up", "ceiling", "roof" }),
        "The roof is supported by wooden rafters.\n");
    add_item( ({ "wall", "walls" }),
        "Which wall do you wish to examine?\n");
    add_item( ({ "fuel", "wood", "wood fuel" }),
        "Wood is piled beside the stove, ready to be cast in for"
      + " fuel.\n");

    add_cmd_item( ({ "door", "the door" }),
                  ({ "open", "close", "push", "pull", "lock", "unlock" }),
        "There doesn't seem to be any reason to fuss with the door here."
      + " It remains unlocked and you can use it to come and go.\n");

    add_indoor_items();

    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("barnyard", "west");
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("Sure, here's a hint. In this room, the Farmer's Wife can"
      + " use your help. You can <ask woman help> to get her to tell"
      + " you what she needs you to do for her.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object    npc;

    if (!present("_tutorial_farmers_wife"))
    {
        npc = clone_object(NPC_DIR + "farmers_wife")->move(this_object());
    }

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    if (CHECK_TUTORIAL_BIT(POTION2_BIT))
    {
        switch(arg)
        {
            case "stove":
                return "Along the northern wall, a wood stove provides"
                  + " a method for both heat and cooking. The potion"
                  + " broth is still there, bubbling away.\n";
                break;
            case "broth":
                return "The potion you brought from Bibbiss has been"
                  + " turned into a bubbling broth that is still"
                  + " sitting on the stove.\n";
                break;
        }
    }

    switch(arg)
    {
        case "stove":
            return "Along the northern wall, a wood stove provides"
              + " a method for both heat and cooking.\n";
            break;
    }
} /* describe */
