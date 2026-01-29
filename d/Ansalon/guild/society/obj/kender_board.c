/*
 * /d/Ansalon/guild/society/obj/kender_board.c
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
 * Common Society guild board.
 * Gwyneth, 1999
 */
inherit "/std/board";
#include "../guild.h"

void
create_board()
{
    seteuid(getuid());
    add_name("wall");
    add_adj("covered");
    set_short("wall covered with pinned up notes");
    set_long("This wall is where Kender post notes of all " + 
        "different sorts. Perhaps something exciting can be found.\n");
    set_board_name(KENDER_BOARD);
    set_num_notes(30);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}

