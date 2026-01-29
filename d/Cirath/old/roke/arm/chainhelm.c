/*
 * chainhelm.c
 *
 * Used in npc/sknight1.c npc/guard1.c npc/guard2.c npc/guard3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_short("chain helmet");
    set_long("The helmet is made of leather and covered with thick chains.\n");
    set_name("helmet");
    set_adj("chain");

    set_ac(15);
    set_am(({-2, 3, -1}));

    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 1900);
    add_prop(OBJ_I_VOLUME, 3000);
}
