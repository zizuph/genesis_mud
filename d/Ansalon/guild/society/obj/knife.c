/* 
 * /d/Ansalon/guild/society/obj/knife.c
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
 * Knife for Kender 
 * Gwyneth, June 1999 
 */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

void
create_weapon()
{
    set_name("knife");
    add_name("junk");
    add_pname("junks");
    set_adj("broken");
    add_adj("belt");
    set_short("dragonarmy belt knife");
    set_long("This knife used to be used for tasks such as skinning " + 
        "game, carving wood, cutting fruit, and the occasional flinging " + 
        "at an attacker. The hilt of this knife is carved with " + 
        "fearsome dragons, which makes you believe that it once belonged " + 
        "to a member of the Dragonarmy.\n");
    set_default_weapon(8, 6, W_KNIFE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_BROKEN, 1);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 120);
}

string
query_recover()
{
    return 0;
}

