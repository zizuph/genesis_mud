/*
 * k_short_sword.c
 *
 * Used in npc/knights.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Calonderiel 94 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("sword");
    set_short("narrow shortsword");
    add_name("shortsword");
    set_adj("narrow");
    set_long("A narrow shortsword with a keen edge.\n");
    set_hit(21);
    set_pen(16);

    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VOLUME, 730);
}
