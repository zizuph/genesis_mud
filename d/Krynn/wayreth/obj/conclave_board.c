/*
 * A normal board.
 * To be used by the conclave of the High Sorcery!
 *
 * 950601 by Rastlin
 *970220 by Teth, modified to be Conclave only read/write (and wiz)
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

    set_short("conclave board");
    set_long("This board is for discussions amongst the Conclave and " +
      "Archmages of the Orders.\n");
    set_board_name(CONCLAVE_BOARD);
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
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

    write("You are not an Archmage or member of the Conclave.\n");
    return 1;
}

public int
block_reader()
{
    set_alarm(1.0, 0.0, &(TP)->remove_prop(TEMP_STDREAD_CHECKED));
    TP->add_prop(TEMP_STDREAD_CHECKED, 1);

    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;

    // Archmages (Greater Wizards and above) can write and read this board
    if(QUERY_IS_ARCHMAGE(TP))
        return 0;

    if(QUERY_WHITE_COUNCIL(TP) || QUERY_RED_COUNCIL(TP) || QUERY_BLACK_COUNCIL(TP))
        return 0;

    write("\nThis board is for Conclave and Archmage discussion only.\n\n");
        return 1;
}

