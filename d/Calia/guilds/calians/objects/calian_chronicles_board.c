// OBJECT:  board

    /* Calia Domain

    HISTORY

    [96-12-27] Created by Uhclem from [C:\CALIA\PALACE\OBJECTS\CH_BOARD.DOC].

    PURPOSE

    This board is for discussions of the Calian Chronicles by members of the
    Guild and Calian wizards. */

// INCLUSIONS AND DEFINITIONS

#pragma save_binary

inherit "/std/board";
#include "defs.h"
#include <std.h>
#include <macros.h>

// OBJECT DEFINITION

void
create_board()

    {

    seteuid(getuid(THIS));
    set_name("board");
    set_short("Calian Chronicles Discussion Board");
    set_board_name(CRPALACE_TEXTS + "calian_chron_msgs");
    set_num_notes(50);
    set_silent(1);
    set_no_report(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);

    }
