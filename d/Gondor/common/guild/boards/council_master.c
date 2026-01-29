/*
 * /d/Gondor/common/guild/boards/council_master.c
 *
 * derived from:
 *
 * /d/Genesis/obj/common_master.c
 *
 * This object is the common board that should contain notes that are
 * important to all players in Genesis. If you want to have a common
 * board in your room, you should clone /d/Genesis/obj/board.c
 *
 * Never clone this board. It is meant to be the central common board
 * that takes care of everything. Boards are very sensitive and we would
 * not like to have problems with it.
 *
 * The original common board was coded by /Nick
 *
 * Complete revision to get rid of all problems with the common board:
 * /Mercade, 23 March 1994
 *
 * Revision history:
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/board";

#include <macros.h>
#include <mail.h>
#include <std.h>
#include "/d/Gondor/defs.h"

#ifndef COUNCIL
#define COUNCIL "/d/Gondor/common/guild/council"
#endif

/*
 * Global variable that will note be saved
 */
static object *clones; /* Cloned copies of this board */
static string *alias_list; /* the AoP team */

/*
 * Function name: create_board
 * Description  : This function is called to create the board.
 */
nomask void
create_board()
{
    seteuid(getuid(this_object()));

    clones = ({ this_object() });

    set_adj("council");
    set_short("council board");

    set_board_name(BOARD_DIR + "councilboard");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL + 1);
    set_remove_str("Sorry, only a wizard may remove the notes.\n");
    set_no_report(0);
    set_keep_discarded(0);

    alias_list = SECURITY->query_team_list("aop");
}

/*
 * Function name: init
 * Desciprtion  : This function is called to link the board-commands
 *                to people who encounter the board.
 */
nomask void
init()
{
    ::init();

    /*
     * Since remove_msg() in /std/board.c is declared nomask for security
     * reasons, this board should use another function that calls the
     * appropriate function in /std/board.c
     */
    add_action("remove_note", "remove");
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
 * Function name: done_editing
 * Description  : This function is called when a note on this board is
 *                completed. It then gives a message to all people that
 *                are in a room with a common board.
nomask void
done_editing(string message)
{
    if (::done_editing(message))
    {
	notify_all_cloned_boards();
    }
}
*/

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
 * Function name: block_reader
 *                block_writer
 * Description  : Only members of Gondor, members of the council of the
 *                rangers and archwizards and keepers may handle this board.
 * Returns      : 1 - it is forbidden to handle the board
 *                0 - it is oke to handle the board
 */
varargs int
block_reader()
{
    string name = this_player()->query_real_name();

    if( (SECURITY->query_wiz_dom(name) == "Gondor") ||
        (member_array(geteuid(this_interactive()), alias_list) >= 0) ||
	(COUNCIL->is_officer(TP->query_name())) ||
	(SECURITY->query_wiz_rank(name) >= WIZ_ARCH) )
    {
	return 0;
    }

    /* test for present added by Mrpr for use with his soul, Mercade */
    if (present(this_interactive(), environment(this_object())))
	write("Only wizards of Gondor and Captains of the Rangers can handle " +
	    "this board.\n");
    return 1;
}

varargs int block_writer() { return block_reader(); }
varargs int
allow_remove()
{
    string name = this_player()->query_real_name();

    if ((SECURITY->query_wiz_dom(name) == "Gondor") ||
      (TP->query_name() == "Olorin") ||
      (TP->query_name() == "Elessar") ||
      (COUNCIL->is_officer(TP->query_name())) ||
      (SECURITY->query_wiz_rank(name) >= WIZ_ARCH))
    {
        return 1;
    }
    if (present(this_interactive(), environment(this_object())))
        write("Only wizards of Gondor and Captains of the Rangers can "
          + "handle this board.\n");
    return 0;
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
