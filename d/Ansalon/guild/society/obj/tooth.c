/* /d/Ansalon/guild/society/obj/tooth.c
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
 * Tooth necklace for Kender 
 * Gwyneth, June 1999 
 */
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("necklace");
    add_name("tooth");
    add_name("junk");
    add_pname("junks");
    set_adj("shark");
    add_adj("tooth");
    set_short("shark tooth necklace");
    set_long("This is a very large tooth! It probably came from a shark. " + 
        "A hole has been drilled into the top, and a string threaded " + 
        "through the hole to make a necklace.\n");
    set_at(A_NECK);
    remove_prop(OBJ_I_VALUE);                                                  
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
}

string
query_recover()
{
    return 0;
}

