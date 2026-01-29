
#pragma save_binary

inherit "std/board.c";
#include "defs.h"
#include <std.h>
#include <macros.h>
#include WORSHIP_HEADER
#include COUNCIL_HEADER

void
create_board()
{
    seteuid(getuid(THIS));
    set_name("board");
    set_short("Elemental Worshippers of Calia Private bulletin board");
    set_board_name(WOR_TEMPLE+"board");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

int
allow_remove()
{
    return (COUNCIL_CODE->is_council_member(TP->query_real_name()));
}

public int
is_worship(object player)
{
    return player->query_guild_name_lay() == GUILD_NAME;
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
    if (!is_worship(TP)
        && TP->query_guild_name_occ() != "Spirit Circle of Psuchae")
    {
        return 1;
    }
         
    return 0;
}

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
block_reader(int note = 0)
{
    if (!is_worship(TP)
        && TP->query_guild_name_occ() != "Spirit Circle of Psuchae")
    {
        return 1;
    }

    return 0;
}
