/*
 * cloak.c
 *
 * Used in npc/ogion.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Copyright (C)
Joshua 941220 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("cloak");
    set_pname("robes");
    add_name("robe");
    set_short("black cloak");
    set_pshort("black cloaks");
    set_long("It is a black cloak.\n");
    set_adj("black");
    set_ac(5);
    set_am(({3, 2, -5}));
    set_at(A_ROBE);
    set_af(this_object());

    add_prop(OBJ_I_VALUE, 93);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 750);
    add_prop(OBJ_S_SEARCH_FUN, "Extra_robe");

}

string
Extra_robe()
{
    return ("The cloak smells awfully.\n");
}
