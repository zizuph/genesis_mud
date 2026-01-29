/* The Union board
 *    Cirion, 032996
 */
#pragma strict_types

inherit "/std/board";
#include <std.h>

#include "../defs.h"

public void
create_board()
{
    set_board_name(GUILDLOG + "council_board");
    set_num_notes(30);
    set_silent(1);
    set_show_lvl(1);
    set_keep_discarded(1);
    set_remove_str("You are not permitted.\n");
    set_short("illuminated board");
}

/* Elders, Avenir wizzes, and Arches only */
public int
block_reader()
{
    string name = TP->query_name();

    if (!IS_ELDER(TP) &&
	SECURITY->query_wiz_rank(name) < WIZ_ARCH &&
	SECURITY->query_wiz_dom(name) != "Avenir")
    {
	if (present(TP), ENV(TO))
	    write("You are not permitted to view this board.\n");
	return 1;
    }

    return 0;
}

public int
block_writer()
{
    return block_reader();
}

/* Arches and Avenir wzards only */
public int
allow_remove()
{ 
    if (TP->query_wiz_rank() >= WIZ_ARCH ||
	SECURITY->query_wiz_dom(TP->query_real_name()) == "Avenir")
	return 1;

    return 0;
}
