/* 
 * /d/Ansalon/guild/society/obj/stocking.c
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
 * Silk stocking for Kender 
 * Gwyneth, June 1999 
 */
inherit "/std/armour";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("stocking");
    add_name("junk");
    add_pname("junks");
    set_adj("black");
    add_adj("silk");
    set_short("black silk stocking");
    set_long("This is a delicate stocking made of black silk. It is fit " + 
        "to be worn over a lady's foot.\n");
    set_slots(A_ANY_FOOT);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 120);
    set_layers(2);
    set_looseness(0);
}

string
query_recover()
{
    return 0;
}

