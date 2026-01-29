/*
 *  /d/Sparkle/area/tutorial/silverdell/common_board_room.c
 *
 *  This is the Common Board for Silverdell.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    28  /* the chapter for the sign */


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
    object   board;

    set_short("the Common Board");
    set_long("You are at the Common Board. This isn't really a game-based"
      + " room so much as it is a place to read important announcements"
      + " from the wizards of Genesis. Take time to <read> the notes on"
      + " the board when you feel like it. When you are ready to leave,"
      + " you can use the <back> command to return to the Town Hall.\n\n");

    prevent_attacks();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("board_room", "back");

    board = clone_object("/d/Genesis/obj/board");
    board->move(this_object());
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
    write("Sure ... here's a hint. Eventually, you should take the time"
      + " to read every note on the common board. They are all important"
      + " announcements that have to do with the game. Don't feel like"
      + " you have to read them all right now, though.\n");
 
    return 1;
} /* hint */
