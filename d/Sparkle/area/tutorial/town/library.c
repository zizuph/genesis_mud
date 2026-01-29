/*
 *  /d/Sparkle/area/tutorial/town/library1.c
 *
 *  This is the main room of the library. This room teaches
 *  players about the help command.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    19  /* the chapter for the sign */


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
    set_short("the main room of the Library of Greenhollow");
    set_long("This is the Library of Greenhollow. Here"
      + " one can sit for long hours and study on various topics."
      + " Reading the tutorial sign will help familiarize you with"
      + " the <help> command. West is a wing of the library"
      + " dedicated to the races found in the lands.\n\n");

    add_item( ({ "library", "here", "building", "area",
                 "greenhollow library", "library of greenhollow" }), long);
    add_item( ({ "wing", "west wing" }),
        "To access the west wing, you would need to travel west.\n");

    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("street_2", "east");
    add_exit("library3", "west");
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
    write("A hint? Sure ... probably the best thing to do is to use the"
      + " <help> command to familiarize yourself with all the commands you"
      + " can use in the game. Don't spend more time on it than you wish,"
      + " and feel free to continue your self-education whenever you feel"
      + " like it.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


