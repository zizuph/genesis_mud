/*
 * Filename:    krynn_disc.c
 * Description: The Master board for Krynn discussions...
 *              use disc_board.c to instanciate a board in a room
 *              of yours.
 *
 * Code taken from the common board.
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/board";

#include <macros.h>
#include <std.h>

#define DISCUSS_ROOM "/d/Krynn/common/domain_office"
/*
 * Global variable that will note be saved
 */
static object *clones; /* Cloned copies of this board */

/*
 * Function name: create_board
 * Description  : This function is called to create the board.
 */
nomask void
create_board()
{
    seteuid(getuid(this_object()));

    clones = ({ this_object() });

    set_board_name("/d/Krynn/common/log/board_data2");
    set_num_notes(80);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Sorry, only a Wizards may remove the notes.\n");
    set_no_report(0);
    set_keep_discarded(1);

    DISCUSS_ROOM->teleledningsanka();
    set_alarm(0.1, 0.0, &move(DISCUSS_ROOM));

}

/*
 * Function name: add_cloned_board
 * Description  : This function will be called each time a common board
 *                is cloned with the objectpointer to the board.
 * Arguments    : object - the objectpointer to the cloned board.
 */
nomask void
add_cloned_board(object board)
{
    if (!clones)
    {
        clones = ({ });
    }

    clones += ({ board });
}

/*
 * Function name: notify_all_cloned_boards
 * Description  : This function gives a message to all rooms that have
 *                a copy of the common board about the fact that the
 *                notes on the board have changed.
 */
nomask void
notify_all_cloned_boards()
{
    int i;

    /* remove all destructed boards. */
    clones -= ({ 0 });

    for (i = 0; i < sizeof(clones); i++)
    {
        if ((objectp(environment(clones[i]))) &&
            (environment(this_player()) != environment(clones[i])))
        {
            tell_room(environment(clones[i]),
                "The notes on the board have changed.\n");
        }
    }
}

/*
 * Function name: post_note_hook
 * Description  : This function is called when a note on this board is
 *                completed. It then gives a message to all people that
 *                are in a room with a common board. Only if the masked
 *                function returns true, a message was added. Otherwise
 *                it is possible that adding the message fails.
 * Arguments    : string head - the header of the note.
 */
nomask void
post_note_hook(string head)
{
    ::post_note_hook(head);

    notify_all_cloned_boards();
}

/*
 * Function name: remove_note
 * Description  : Since remove_msg() is declared nomask in /std/board
 *                this function is created.
 * Arguments    : int - the note to remove
 * Returns      : int - whatever was returned from remove_msg()
 */
nomask int
remove_note(int what_msg)
{

    int result = remove_msg(what_msg);

    if (result)
    {
        notify_all_cloned_boards();
    }

    return result;
}

/*
 * Function name: query_prevent_shadow
 * Description  : This function is to make sure that this object is never
 *                shadowed.
 * Returns      : 1 - always.
 */
nomask int
query_prevent_shadow()
{
    return 1;
}
