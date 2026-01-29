/*
 * cpmail.c
 *
 * Used in npc/towerg1.c npc/towerg2.c npc/towerg3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("platemail");
    add_name(({"mail", "plate"}));
    set_adj("copper");
    set_short("copper platemail");
    set_long("It's green from copper oxide.\n");
    set_ac(15);
    set_at(A_BODY);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 6000);
}
