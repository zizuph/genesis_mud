/* 
 * /d/Ansalon/guild/society/obj/sbelt.c
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
 * Silk belt for Kender 
 * Gwyneth, June 1999  
 */
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("belt");
    add_name("junk");
    add_pname("junks");
    set_adj("scarlet");
    add_adj("silk");
    set_short("scarlet silk belt");
    set_long("This is a finely crafted scarlet silk belt worn by nobles.\n");
    set_at(A_WAIST);
    remove_prop(OBJ_I_VALUE);                                                  
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 120);
}

string
query_recover()
{
    return 0;
}

