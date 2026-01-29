/*
 * k_round_shield.c
 *
 * Used in npc/knights.c
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
    set_name("shield");
    add_name("round-shield");
    set_short("small round-shield");
    set_long("A small round_shield emblazoned with an angry red firebolt" +
             " inside a black cloud.\n");
    set_at(A_SHIELD);
    set_ac(15);

    add_prop(OBJ_I_VOLUME, 1150);
}
