/*
 * A policy board.
 * To be used by the conclave of the High Sorcery!
 *
 * 950601 by Rastlin
 *
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <std.h>

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));

    set_short("policy board");
    set_board_name(POLICY_BOARD);
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_str("Only a member of the Conclave may remove notes.\n");
    set_no_report(0);
    set_keep_discarded(0);
}

public int
block_writer()
{
    // Archmages (Greater Wizards and above) can write and read this board
    if(QUERY_IS_ARCHMAGE(TP))
        return 0;

    if(QUERY_WHITE_COUNCIL(TP) || QUERY_RED_COUNCIL(TP) || QUERY_BLACK_COUNCIL(TP))
        return 0;

    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;

    write("You are not an Archmage or member of the Conclave. You cannot write " +
        "a note on this board.\n");
    return 1;
}

public varargs int
allow_remove(int note)
{
    if(QUERY_WHITE_COUNCIL(TP) || QUERY_RED_COUNCIL(TP) || QUERY_BLACK_COUNCIL(TP))
        return 1;

    return 0;
}


