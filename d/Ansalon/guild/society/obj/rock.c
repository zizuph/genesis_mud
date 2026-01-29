/* 
 * /d/Ansalon/guild/society/obj/rock.c
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
 * Piece of rock found in Kendermore 
 * Gwyneth, 1999 
 */
inherit "/std/heap.c";

#include <macros.h>
#include <stdproperties.h>

public void
create_heap()
{
    set_name(({"rock", "junk"}));
    set_pname(({"rocks", "junks"}));
    set_short("shiny rock");
    set_adj("shiny");
    set_long("This rock is a plain dull gray on the outside, but on the " +
        "inside, shiny purple crystals have been exposed.\n");
    set_heap_size(1);

    add_prop(HEAP_I_UNIT_WEIGHT, 10);
    add_prop(HEAP_I_UNIT_VOLUME, 10);
    add_prop(HEAP_I_UNIT_VALUE, 0);

    add_prop(HEAP_S_UNIQUE_ID, MASTER + ":" + singular_short(this_object()));
}

