/*
 * /d/Ansalon/guild/society/obj/voting_board.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * The board for voting members.
 * Gwyneth, 1999
 */
#include <macros.h>
#include "../guild.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(this_object()));
    add_name("wall");
    add_adj("covered");
    set_short("wall covered with papers");
    set_long("This wall is where Kender post notes of " + 
        "about the kender hopefuls who want to join the Secret " +
        "Society of Uncle Trapspringer. Perhaps something " +
        "exciting can be found here.\n");
    set_board_name(KVOTE_BOARD);
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
}

