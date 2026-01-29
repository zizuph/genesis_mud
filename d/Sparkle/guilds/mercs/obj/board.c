/*
 * /d/Genesis/guilds/merc/obj/board.c
 *
 */
inherit "/std/board";

#include "../merc.h"

public void
create_board()
{
    seteuid(getuid(this_object()));
    set_long("Mercenaries may share information here.\n");
    set_board_name(MBOARD);
    set_num_notes(40);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}
