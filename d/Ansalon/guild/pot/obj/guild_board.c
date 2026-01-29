#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_board_name("/d/Ansalon/guild/pot/log/board/pot");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
    set_long("This is the bulletin board for the Priests of Takhisis " +
        "guild.\n");
    set_adj("large");
    set_no_show_composite(1);
}

int
deny_access()
{
    string dom;

    if (TP->query_guild_name_occ() == GUILD_NAME)
        return 0;

    dom = SECURITY->query_wiz_dom(TP->query_real_name());
    if (dom == "ansalon")
        return 0;

    return 1;
}

int
block_reader(int note = 0)
{
    return deny_access();
}

int
block_writer()
{
    return deny_access();
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
allow_remove(int note)
{
    if(GUILD_LEADER(TP))
        return 1;

    return 0;
}
