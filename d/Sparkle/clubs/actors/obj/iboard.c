/*
 * Internal Club Board
 * 
 * Only used by members.
 *
 * 2008-01-25 : Lunatari
 * Increased the max posts to 80
 */
inherit "/std/board";

#include <macros.h>
#include <std.h>

#include "actor.h"

#undef IS_WIZ
#define IS_WIZ(ob)    		(SECURITY->query_wiz_rank((ob)->query_real_name()) != WIZ_MORTAL)

public nomask void
create_board()
{
    seteuid(getuid(this_object()));
    set_board_name(AC_IBOARDVAR);
    set_num_notes(80);
    set_silent(1);
    set_show_lvl(0);
    set_no_report(0);
    set_keep_discarded(0);
    set_remove_rank(99);
}

public nomask int
block_reader()
{
    if (!CHECK_MEMBER(TP) && !IS_WIZ(TP))
    {
	tell_object(this_player(), "Only members of the Actors Club and wizards may read this board.\n");
	return 1;
    }

    return 0;
}

public nomask int
block_writer()
{
    if (!CHECK_MEMBER(TP) && !IS_WIZ(TP))
    {
	tell_object(this_player(), "Only members of the Actors Club and wizards may write on this board.\n");
	return 1;
    }
    return 0;
}

public nomask int
allow_remove()
{
    if (!CHECK_MEMBER(TP) && !IS_WIZ(TP))
    {
	tell_object(this_player(), "Only members of the Actors Club and wizards may remove notes on this board.\n");
	return 0;
    }
    return 1;
}
