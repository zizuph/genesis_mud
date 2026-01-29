/*
 *  /d/Sparkle/area/tutorial/farm/barn.c
 *
 *  This is the hayloft of the barn north of Greenhollow. Here,
 *  the farmers daughter likes to play. Evil players can kill
 *  her if they desire, at the behest of Baron von Krolock.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* prototypes */
public void        create_silverdell();
public void        init();
public int         do_climb(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("up in a hayloft");
    set_long("You are up in a hayloft. A wide window looks down over"
      + " the barnyard from this second level of the barn where bales"
      + " of hay have been stacked on both sides of the room. The floor"
      + " ends abruptly about halfway across the barn, where a ladder"
      + " descends to the ground below.\n\n");

    add_item( ({ "here", "area", "room", "barn", "sturdy barn",
                 "structure", "loft", "hayloft" }), long);
    add_item( ({ "wall", "tall wall", "walls", "tall walls",
                 "barn walls", "barn wall", "wall of the barn",
                 "walls of the barn" }),
        "Though clearly old, the walls of the barn look sturdy enough"
      + " to stand for many more years. Bales of hay have been stacked"
      + " up against them here.\n");
    add_item( ({ "door", "doorway", "doors", "barn door",
                 "barn doors", "east", "east wall", "breeze",
                 "eastern wall" }),
        "The barn doors stand open, down on the ground floor of"
      + " the barn.\n");
    add_item( ({ "implement", "implements", "tool", "tools",
                 "supply", "supplies" }),
        "You can see many tools down below. There aren't any up"
      + " here in the loft.\n");
    add_item( ({ "ground", "down", "floor", "earth", "hard earth",
                 "ground below", "plank", "planks" }),
        "The floor of the loft is made up of planks of wood. Down"
      + " on the ground below, it is hard earth.\n");
    add_item( ({ "up", "roof", "ceiling", "rafter", "rafters" }),
        "The rafters of the barn are just overhead, looking down on"
      + " the hayloft and the ground below.\n");
    add_item( ({ "hay", "bale", "bales", "bale of hay", "bales of hay",
                 "pile", "pile of hay" }),
        "Bales of hay are crowded into the corners of the loft.\n");
    add_item( ({ "ladder" }),
        "The ladder leads from the hayloft down to the ground. You could"
      + " probably try to <climb> down it if you wished.\n");
    add_item( ({ "outside", "barnyard", "yard", "glare", "sun",
                 "window", "farm" }),
        "The window looks down over the barnyard, and has an excellent"
      + " view of the whole farm.\n");

    add_indoor_items();

    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("barn", "down", 0, 1, 1);
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_climb, "climb");
} /* init */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object    npc;

    if (!present("_tutorial_farmers_daughter"))
    {
        npc = clone_object(
                  NPC_DIR + "farmers_daughter")->move(this_object());
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
        "[down] [the] 'ladder' [to] [the] [ground] [below]"))
    {
        return 0; /* bad syntax */
    }

    this_player()->command("$down");

    if (this_player()->query_wiz_level())
    {
        write("Normally we would use move the player 'down' here using"
          + " command. Since you're a wizard, that won't work. Just type"
          + " 'down' yourself.\n");
    }

    return 1;
} /* do_climb */

