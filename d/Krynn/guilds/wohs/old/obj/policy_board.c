/*
 * A policy board.
 * To be used by the conclave of the High Sorcery!
 *
 * 950601 by Rastlin
 *
 */

#include <macros.h>
#include "../guild.h"
#include <std.h>

inherit "/std/board";

#define TP this_player()

void
create_board()
{
    setuid();
    seteuid(getuid());
    
    set_short("policy board");
    set_board_name(LOG + "board_policy");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MAGE);
    set_remove_str("Only a Mage or higher may remove the notes!\n");
    set_no_report(0);
    set_keep_discarded(0);
}

public int
block_writer()
{
    if (ADMIN->query_conclave_member(TP->query_real_name()))
        return 0;

    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;
    
    write("You are not a member of the conclave.\n");
    return 1;
}


