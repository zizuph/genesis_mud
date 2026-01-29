/* 
 * /d/Ansalon/guild/society/obj/peach.c
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
 * Peach for Kender 
 * Gwyneth, June 1999 
 */
inherit "/std/food";

void
create_food()
{
    set_name("peach");
    set_pname("peaches");
    add_name("junk");
    add_pname("junks");
    set_adj("small");
    add_adj("green");
    set_short("small juicy peach");
    set_pshort("small juicy peaches");
    set_long("This is a small juicy peach.\n");
    set_amount(50);
}

