/*
 *  /d/Sparkle/area/tutorial/town/dwarf_start.c
 *
 *  The dwarf racial startlocation in Silverdell.
 *  This room teaches about recovery and glowing items.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    31  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public int         start(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("near a cave in the woods");
    set_long("You stand beside a mine shaft in the woods."
      + " This is a place where dwarves may <start here> to have this"
      + " become their start location. Read the tutorial sign"
      + " for more details.\n\n");

    add_item( ({ "grove", "trees", "grove of trees", "woods" }),
        "Trees surround you here, bordering the mine shaft on all sides."
      + " Leaves from the trees rustle every so often when the breeze"
      + " comes through the grove.\n");
    add_item( ({ "leaves", "leaf", "breeze" }),
        "An occasional breeze blows through the leaves in the trees,"
      + " creating a peaceful and relaxing ambiance.\n");
    add_item( ({ "mine", "shaft", "mine shaft" }),
        "This mine shaft looks completely comfortable and welcoming."
      + " In fact, you could scarcely imagine a better place to wake"
      + " up every morning. Perhaps you should <start here> to make"
      + " this place your home.\n");

    add_outdoor_items();

    prevent_attacks();
    reset_room();

    add_exit("street_6", "southeast");
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
    add_action(start, "start");
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
    write("Need a hint? Sure ... If you so desire, you can set this"
      + " to be your start location. By doing so, you will start here"
      + " whenever you log in. You can return to the road by travelling"
      + " southeast.\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        start
 * Description  :        allow players to try to set this as
 *                       their start location.
 * Arguments    :        string arg - what the player typed after
 *                                    "start"
 * Returns      :        1 - success, 0 - failure
 */
int start(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("You must type <start here> to start here.\n");
        return 0;
    }

    if(this_player()->query_race() != "dwarf")
    {
        notify_fail("Only dwarves may start here.\n");
        return 0;
    }

    if (arg != "here")
    {
        notify_fail("What? Do you wish to <start here> ?\n");
        return 0; /* bad syntax */
    }

    if (this_player()->set_default_start_location(
        file_name(this_object())))
    {
        write("You will start here from now on.\n");
    }
    else
    {
        write("For some reason, you were unable to start here. Please"
          + " make a bug report.\n");
    }

    return 1;
} /* start */

