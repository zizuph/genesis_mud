/*
 *  /d/Sparkle/area/tutorial/farm/barn.c
 *
 *  This is the barn north of Greenhollow. This is where the
 *  Farmer gives out quests. This room teaches about leftovers.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <ss_types.h>
#include <stdproperties.h>

/* global variables */
#define     TUTORIAL_CHAPTER        40       /* chapter for the sign   */
#define     NEEDED_SKILL            10       /* to sneak up the ladder */

/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public int         do_climb(string arg);
public int         check_exit();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("in a sturdy barn");
    set_long("You stand in a sturdy barn. The tall walls of this"
      + " structure rise high above you on all sides. Various tools"
      + " and supplies line the walls and floor. A large pile of hay"
      + " rests on the floor beneath a ladder which leads up to a"
      + " hayloft above. Sturdy wooden doors open onto the barnyard"
      + " to the east.\n\n");

    add_item( ({ "here", "area", "room", "barn", "sturdy barn",
                 "structure" }), long);
    add_item( ({ "wall", "tall wall", "walls", "tall walls",
                 "barn walls", "barn wall", "wall of the barn",
                 "walls of the barn" }),
        "Though clearly old, the walls of the barn look sturdy enough"
      + " to stand for many more years. They are lined with various"
      + " tools and supplies.\n");
    add_item( ({ "door", "doorway", "doors", "barn door",
                 "barn doors", "east", "east wall", "breeze",
                 "eastern wall" }),
        "The barn doors stand open, allowing an occasional breeze to"
      + " filter into the barn.\n");
    add_item( ({ "implement", "implements", "tool", "tools",
                 "supply", "supplies" }),
        "The Farmer and his wife appear to own all of the necessary"
      + " tools and implements to keep the farm going. The barn is"
      + " full of them.\n");
    add_item( ({ "ground", "down", "floor", "earth", "hard earth" }),
        "The floor of the barn is nothing but hard earth.\n");
    add_item( ({ "up", "roof", "ceiling", "rafter", "rafters" }),
        "The rafters of the barn are high overhead, looking down on"
      + " the hayloft and the ground below.\n");
    add_item( ({ "loft", "hayloft" }),
        "Above the ground, a second level of the barn looks like any"
      + " typical hayloft. A ladder leads from the ground up to it."
      + " You could probably <climb> the ladder if you tried.\n");
    add_item( ({ "hay", "bale", "bales", "bale of hay", "bales of hay",
                 "pile", "pile of hay" }),
        "Hay is everywhere in the barn. Bales are visible in the loft,"
      + " and a large pile rests on the ground here near the ladder.\n");
    add_item( ({ "ladder" }),
        "The ladder leads from the ground up to the hayloft. You could"
      + " probably try to <climb> it if you wished.\n");
    add_item( ({ "outside", "barnyard", "yard", "glare", "sun" }),
        "The barnyard is visible through the doors to the east, but"
      + " it is hard to see anything through the glare of the sun.\n");

    add_cmd_item( ({ "door", "the door" }),
                  ({ "open", "close", "push", "pull", "lock", "unlock" }),
        "There doesn't seem to be any reason to fuss with the barn doors."
      + " They remain open whenever Farmer Brown is present.\n");

    add_indoor_items();

    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("barnyard", "east");
    add_exit("hayloft", "up", check_exit, 1, 1);
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
    add_action(do_climb, "climb");
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
    write("Sure, here's a hint. In this room, Farmer Brown can"
      + " use your help. You can <ask farmer help> to get him to tell"
      + " you what he needs you to do.\n");
 
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

    if (!present("_tutorial_farmer_brown"))
    {
        npc = clone_object(NPC_DIR + "farmer_brown")->move(this_object());
    }

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        do_climb
 * Description  :        allow players to try to climb the ladder
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise.
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] 'ladder' [to] [the] [hay] [loft] [hayloft]"))
    {
        return 0; /* bad syntax */
    }

    this_player()->command("$up");

    if (this_player()->query_wiz_level())
    {
        write("Normally we would use move the player 'up' here using"
          + " command. Since you're a wizard, that won't work. Just type"
          + " 'up' yourself.\n");
    }

    return 1;
} /* do_climb */


/*
 * Function name:        check_exit
 * Description  :        The farmer doesn't allow people to climb up
 *                       into the hayloft. But players can sneak past
 *                       with high enough skill.
 * Returns      :        int 1 - don't alow, 0 - allow
 */
public int
check_exit()
{
    if (!present("_tutorial_farmer_brown", this_object()))
    {
        write("You climb up the ladder into the hayloft.\n");
        return 0;
    }

    if (this_player()->query_skill(SS_SNEAK) >= NEEDED_SKILL)
    {
        write("Using your skill, you sneak to the ladder and scurry up"
          + " it when Farmer Brown isn't looking.\n");
        return 0;
    }

    write("Farmer Brown stops you from climbing the ladder. If you"
      + " were to train your sneak skill a bit higher, perhaps you"
      + " could slip past him.\n");

    if (this_player()->query_wiz_level())
    {
        write("Since you're a wizard, you climb up anyway.\n");
        return 0;
    }
    return 1;
} /* check_exit */

