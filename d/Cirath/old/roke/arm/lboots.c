/*
 * lboots.c
 *
 * Used in npc/sknight1.c npc/towerg1.c npc/towerg2.c npc/towerg3.c
 * Used in npc/towerg4.c npc/kobold1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_am(({0, 0, 0}));
    set_name("boots");
    set_adj("leather");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    set_long("The boots looks as if they have seen many battles.\n");
    set_ac(10);
    set_at(A_FEET | A_LEGS);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 3000);
}
