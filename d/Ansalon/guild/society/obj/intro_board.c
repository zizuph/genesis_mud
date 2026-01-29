/*
 * /d/Ansalon/guild/society/obj/intro_board.c
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
 * Coded by Gwyneth
 * Modification log:
 *   Gwyneth - 06/01/04 - Changed read/write perms on the board.
 */
#include <macros.h>
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid());
    add_name("corkboard");
    add_adj("cork");
    set_short("corkboard");
    set_long("This corkboard is where kender hopefuls of the " +
        "Secret Society of Uncle Trapspringer can introduce " +
        "themselves to the members. It is of course, not required " +
        "to do so, but considered an easy way to let them know " +
        "a bit about yourself.\n");
    set_board_name(KINT_BOARD);
    set_num_notes(30);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
}

public varargs int
block_reader(int note = 0)
{
    if (MEMBER(this_player()) ||
      this_player()->query_wiz_level())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

public int
block_writer()
{
    string name = this_player()->query_real_name();

    if (!objectp(this_player()))
        return 1;

    if (VMASTER->query_banished(name) || VMASTER->query_enemy(name))
    {
        write("As you are banished from joining this guild, you " +
            "are not allowed to post on the application board.\n");
        return 1;
    }
}
