/*
 *  /d/Sparkle/area/tutorial/town/tavern2.c
 *
 *  This side room to the Greenhollow tavern teaches
 *  about many social commands.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    18  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("the side room of the Red Weasel Tavern");
    set_long("This appears to be a side room off the main hall of"
      + " the Red Weasel Tavern. People are crowded around in"
      + " here, laughing and having friendly conversations with"
      + " one another. It seems like a great place to socialize"
      + " and get to know people. Read the tutorial sign for more"
      + " information.\n\n");

    add_item( ({ "here", "area", "tavern", "weasel", "red weasel",
                 "red weasel tavern", "side room" }),
        "This room is just off the main hall of the tavern which"
      + " is visible to the east. It seems like certain regulars"
      + " come in here to laugh and have a good time together.\n");
    add_item( ({ "main hall", "bar", "bartender" }),
        "The bartender is visible behind the bar in the main hall"
      + " to the east.\n");
    add_item( ({ "regulars", "regular", "people", "person" }),
        "There are a number of people crowded around you here. Most"
      + " of them are laughing and having a good time together."
      + " It might be a good idea to <introduce myself> here so you"
      + " can get better at meeting people.\n");
    add_item( ({ "table", "tables" }),
        "Tables have been set up around the room for the patrons to"
      + " sit at.\n");

    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("tavern", "east");
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
    write("Sure, here's a hint. This room is a good place to test"
      + " out the social commands. You should <introduce me> to the"
      + " NPCs in this room. Actually, you might want to try it to"
      + " the NPCs elsewhere in town also.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object    npc1;
    object    npc2;

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

    if (!present("_patron_1"))
    {
        npc1 = clone_object(NPC_DIR + "bar_patron1")->move(this_object());
    }

    if (!present("_patron_2"))
    {
        npc2 = clone_object(NPC_DIR + "bar_patron2")->move(this_object());
    }
} /* reset_room */


