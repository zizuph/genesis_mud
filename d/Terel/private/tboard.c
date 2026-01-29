// The domain's private board, by Shinto.
inherit "/std/board";

#include <std.h>
#include <macros.h>

/* These are the special wizards who can read this board. */
#define ALLOWED ({ "tomas", "teth", "gaidin", "zima" })

void
create_board() 
{
    setuid();
    seteuid(getuid(this_object()));

    set_short("The Private Board of Terel");
    set_board_name(MASTER_OB(this_object()));
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("It is not permitted.\n");
}

/*
 * Function name: block_writer
 * Description  : This function will return true if this_player() may not
 *                read/write on the board. Note that players may always read
 *                their own notes, but this is not checked here.
 * Returns      : int 1/0 - true if the player may read.
 */
public nomask int
block_writer()
{
    return (member_array(this_interactive()->query_real_name(), ALLOWED) == -1);
}

public nomask int
block_reader()
{
    return block_writer();
}
