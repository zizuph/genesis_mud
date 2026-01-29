/*
 * /d/Gondor/common/militia/obj/board.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Coded by Auberon and Gwyneth
 */
inherit "/d/Gondor/std/board";

#include "../militia.h"

public void
create_board()
{
    seteuid(getuid(this_object()));
    set_long("This is where members of the militia may post notes.\n");
    set_board_name(MBOARD);
    set_num_notes(40);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}
