/*
 * File         : /d/Genesis/new/board.c
 * Creator      : Teth@Genesis
 * Copyright    : Daniel Mosquin
 * Date         : October 1, 1998
 * Modifications: 
 * Purpose      : This is the board for start location discussion.       
 * Related Files: /d/Genesis/new/common.c (clones the board)
 *              : /d/Genesis/wiz/boards/startloc/
 * Comments     : The above directory stores the notes from this board.
 *                This file is to be deleted upon the transfer of the
 *                new start locations to /d/Genesis/start/
 * TODO         :
 */

/* Inherit the basic board object, which contains all of the standard
 * board functions. It also gives some basic configuration.
 */
inherit "/std/board"; 

/* Include the following files as headers to this file. Use the format
 * of <filename.h> in this case, since the location of filename.h is already
 * predefined. Including "/sys/filename.h" would also work, but it is
 * extremely poor form, as it will not work if ever /sys/filename.h is moved.
 * We want to include this header because of some definitions below.
 */
#include <std.h>

/*
 * Function name: create_board
 * Description  : It creates the board object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_board()
{
    /* Set a directory for the notes to be saved in. */
    set_board_name("/d/Genesis/wiz/boards/startloc");

    /* Set the amount of notes that the board may contain. */
    set_num_notes(50);

    /* Set this board silent (no read or examine messages). */
    set_silent(1);

    /* Allow only wizards++ to remove notes. */
    set_remove_rank(WIZ_NORMAL); // WIZ_NORMAL is defined in /sys/std.h

    /* Since the default remove rank was changed, change the default remove
       message. */
    set_remove_str("Only a Wizard or higher can remove other's notes.\n"); 
}

/*
 * Function name: reset_board
 * Description  : This function is called from reset_object() in the standard
 *                board object. It allows redefinition of what occurs upon
 *                a reset of this particular board.
 * Arguments    :
 * Returns      :
 */
public void
reset_board()
{
    if (!random(4))
    {
        tell_room(environment(),
          "The very-attentive-to-details Arch of Domains appears and " +
          "secures some notes on the " + short() + " that were loose. " +
          "The Arch of Domains then remembers something else he needs to " +
          "do, so he quickly leaves.\n");
    }
}
