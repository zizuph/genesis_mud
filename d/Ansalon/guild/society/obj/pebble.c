/* 
 * /d/Ansalon/guild/society/obj/pebble.c
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
 * Pebble that clones when a kender 'collects' pebbles.
 * Gwyneth, 1999 
 */
inherit "/std/heap.c";
#include <macros.h>
#include <stdproperties.h>

public void
create_heap()
{
    set_name("pebble");
    set_pname("pebbles");
    set_short("small round pebble");
    set_pshort("small round pebbles");
    set_adj("small");
    add_adj("round");
    set_long("This is a small round pebble, perfect for a slingshot!\n");
    set_heap_size(1);

    add_prop(HEAP_I_UNIT_WEIGHT, 10);
    add_prop(HEAP_I_UNIT_VOLUME, 10);
    add_prop(HEAP_I_UNIT_VALUE, 0);
    add_prop(HEAP_S_UNIQUE_ID, MASTER + ":" + singular_short(this_object()));
}

