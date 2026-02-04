/*
 * Vampire Bulletin Board
 *
 * This is a bulletin board that only Vampires should be able to
 * read. Used for discussion of guild specific things.
 *
 * Created by Petros, April 2009
 */
 
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../guild.h"

inherit "/std/board";

public void
create_board()
{
    seteuid(getuid(TO));
    set_board_name(VAMP_DIR + "vampire_board");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(1);
    set_no_show_composite(1);

    set_name( ({ "board", "vampire board" }) );
    set_short("vampire board");
    set_long("This board has been placed against the wall opposite of "
        + "the tapestry through which you came. It looks like you can "
        + "read and post discussions with others whom you share "
        + "eternity with.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
}

public void
reset_board()
{
    // Masked so the silly gnome doesn't come by
}

public int
vampire_board_check()
{
    if (IS_VAMP(this_player())
        || this_player()->query_wiz_level())
    {
        return 1;
    }
    
    return 0;
}


/* Stop unwanted people reading, writing or removing notes */
/*
 * Function name: block_reader
 * Description  : If this_player() is not allowed to read notes of other
 *                people on this board, this function should be used to
 *                block access. If you print an error message on failure,
 *                please check whether this_player() is in the environment
 *                of the board.
 *                Redefine this function in your board code. It gets called
 *                automatically when someone tries to read.
 * Arguments      int note - Optional argument with the number of the note
 *                    the person wants to read. When 0, basic access to the
 *                    board.
 * Returns      : int - true if the player is NOT allowed to read.
 */
public varargs int 
block_reader()
{
    return !vampire_board_check();
}

/*
 * Function name: allow_remove
 * Description  : This function checks whether this_player() is allowed
 *                to remove notes from this board. If you print an error
 *                message on failure, please check whether this_player()
 *                is in the environment of the board. This function works
 *                independant of the set_remove_rank function.
 * Arguments    : int note - the optional number of the note to be removed.
 *                    When 0, just general access is meant.
 * Returns      : int - true if the player is allowed to remove notes.
 */
public varargs int 
allow_remove()
{
    return vampire_board_check();
}

/*
 * Function name: block_writer
 * Description  : If this_player() is not allowed to write notes on this
 *                board, this function should be used to block access.
 *                If you print an error message on failure, please check
 *                whether this_player() is in the environment of the board.
 *                Redefine this function in your board code. It gets called
 *                automatically when someone tries to write.
 * Returns      : int 1/0 - true if the player is NOT allowed to write.
 */
public int 
block_writer()
{
    return !vampire_board_check();
}
