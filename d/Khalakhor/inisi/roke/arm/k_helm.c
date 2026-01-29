/*
 * k_helm.c
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
    set_name("helm");
    add_name("helmet");
    set_adj("iron");
    set_short("iron helm");
    set_pshort("iron helms");
    set_long("An iron helm with a small nose-guard.\n");

    set_ac(18);
    set_am(({0, 0, 0}));
    set_at(A_HEAD);

    add_prop(OBJ_I_VOLUME, 523);
}
