/* 
 * /d/Ansalon/guild/society/obj/slipper.c
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
 * Slipper for Kender
 * Gwyneth, June 1999 
 */
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("slipper");
    add_name("junk");
    add_pname("junks");
    set_adj("pink");
    add_adj("lady's");
    set_short("pink lady's slipper");
    set_long("This delicate slipper is meant for a lady's foot. It is " + 
        "meant mainly for decoration, as anything rougher than a smooth " + 
        "marble floor would soon wear on it.\n");
    set_at(A_ANY_FOOT);
    set_ac(0);
    remove_prop(OBJ_I_VALUE);                                                  
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 120);
}

string
query_recover()
{
    return 0;
}

