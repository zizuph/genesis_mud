/*
 * k_kite_shield2.c
 *
 * Used in npc/knights.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Calonderiel 94 */
/*  added add_adj for "large" and "kite" (Amelia 7/20/97)
*/

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("shield");
    add_name("kite-shield");
    add_adj(({"large", "kite"}));
    set_short("large kite-shield");
    set_long("A large kite_shield emblazoned with an angry red firebolt" +
             " inside a black cloud.\n");
    set_at(A_SHIELD);
    set_ac(25);

    add_prop(OBJ_I_VOLUME, 1750);
}

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({A_BODY}));
}
