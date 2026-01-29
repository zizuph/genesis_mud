/*
 * kingmail.c
 *
 * Used in npc/kingghost.c
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
    set_short("mithril platemail");
    set_long("This is an excellent piece of dwarven craftmanship.\n");

    set_name("platemail");
    add_name("mail");

    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 10000);

    set_adj("mithril");
    add_adj("plate");

    set_ac(40);
}
