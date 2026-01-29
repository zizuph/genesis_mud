/* This is the Grunts guild bulletin board. */
/* Recoded on 21/08/95 by Tulix III.        */

inherit "std/board";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"

public void
create_board()
{
    set_short("The Grunts' bulletin board");
    set_board_name(GRUNTS_DIR + "obj/grunts_notes");
    set_num_notes(100);
/*
    set_err_log(GRUNTS_DIR + "obj/board_errors");
*/
    set_silent(0);
    set_show_lvl(1);
}
