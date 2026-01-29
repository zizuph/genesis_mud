/*
 * A normal board.
 * To be used by the conclave of the High Sorcery!
 *
 * 950601 by Rastlin
 *970220 by Teth, modified to be Conclave only read/write (and wiz)
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <std.h>

#include "../guild.h";

inherit "/std/board";

void
create_board()
{
    setuid();
    seteuid(getuid(TO));

    set_short("spell board");
    set_board_name(LOG + "board_magic");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("Only an Arch or higher may remove the notes!\n");
    
    set_no_report(0);
    set_keep_discarded(0);
}

public int
block_writer()
{
    if (ADMIN->query_conclave_member(TP))
        return 0;

    if (SECURITY->query_wiz_domain(TP->query_real_name()) == "Krynn")
        return 0;
    
    if (environment() == environment(TP))
    	write("You are not a member of the conclave.\n");
    return 1;
}

public int
block_reader()
{
    if (SECURITY->query_wiz_domain(TP->query_real_name()) == "Krynn")
        return 0;
    
    if (!(ADMIN->query_conclave_member(TP)))
    {
	if (environment() == environment(TP))
            write("This board is for Conclave Magic  discussion only.\n");
        return 1;
    }
    return 0;
}

