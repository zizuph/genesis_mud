/*
 * /d/Ansalon/guild/society/obj/box.c
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
 * Donation box.
 *
 * Gwyneth, July 1999
 */
inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"

void
create_container()
{
    set_name("box");
    set_adj("old");
    set_short("old box");
    set_long("This is an old wooden box sitting next to the wall. It has " + 
        "the word 'Donations' printed on a metal plaque on the side.\n");

    add_item("plaque", "It reads: Donations.\n");

    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_NO_REM, "@@check_kender@@");
    add_prop(OBJ_M_NO_GET, "The old box is fastened to the wall.\n");
}

mixed
check_kender()
{
    if (MEMBER(this_player()))
        return 0;

    else
        return "Sorry, only members of this guild can take items from " + 
            "the box.\n";
}
