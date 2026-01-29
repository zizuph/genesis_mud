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
#include "../guild/local.h"
#include <std.h>

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));

    set_short("conclave board");
    set_board_name(CONCLAVE_BOARD);
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

public int
block_reader()
{
    set_alarm(1.0, 0.0, &(TP)->remove_prop(TEMP_STDREAD_CHECKED));
    TP->add_prop(TEMP_STDREAD_CHECKED, 1);
    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;
    if (!(ADMIN->query_conclave_member(TP->query_real_name())))
    {
        write("This board is for Conclave discussion only.\n");
        return 1;
    }
    return 0;

}

