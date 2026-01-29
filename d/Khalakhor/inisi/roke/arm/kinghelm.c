/*
 * kinghelm.c
 *
 * Used in npc/kingghost.c
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
    set_short("mithril helmet");
    set_long("This is an excellent piece of dwarven craftmanship.\n");

    set_name("helmet");

    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1700);

    set_adj("mithril");

    set_ac(25);
}
