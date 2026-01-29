/*
 * k_splintmail.c
 *
 * Used in npc/knights.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Calonderiel 94 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("splintmail");
    add_name("mail");
    set_adj("polished");
    set_short("polished splintmail");
    set_pshort("polished splintmails");
    set_long("A splintmail that has been polished to a high shine.\n");

    set_ac(22);
    set_am(({-1, 1, 0}));
    set_at(A_TORSO);

    add_prop(OBJ_I_VOLUME, 1230);
    add_prop(OBJ_I_WEIGHT, 4530);
}
