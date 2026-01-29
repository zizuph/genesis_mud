/*
 * kingaxe.c
 *
 * Used in npc/kingghost.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{
    set_name("axe");
    set_adj("mithril");
    set_short("mithril axe");
    set_long("A powerful mithril axe, made by dwarven weaponsmiths.\n");

    set_hit(21);
    set_pen(37);

    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
}
