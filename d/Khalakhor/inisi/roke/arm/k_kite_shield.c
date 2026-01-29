/*
 * k_kite_shield.c
 *
 * Used in npc/knights.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Calonderiel 94 */
/* 7/20/97 corrected typo (Amelia)
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
    add_adj("kite");
    set_short("kite-shield");
    set_long("A kite-shield emblazoned with an angry red firebolt" +
             " inside a black cloud.\n");
    set_at(A_SHIELD);
    set_ac(20);

    add_prop(OBJ_I_VOLUME, 1340);
}

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({A_BODY}));
}
