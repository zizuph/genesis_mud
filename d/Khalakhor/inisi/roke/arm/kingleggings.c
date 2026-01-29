/*
 * kingleggings.c
 *
 * Used in npc/kingghost.c
 *
 * Created from gauntlets by old Roke
 * Tapakah, July 2011.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("leggings");
    /*
       set_pname("pairs of mithril guantlets");
     */
    set_adj("mithril");
    add_adj("pair of");

    set_short("pair of mithril leggings");
    set_long("The leggings are made of shining mithril alloy. " +
             "They seem large enough to protect your legs as well " +
             "as your feet.\n");

    set_at(A_LEGS | A_FEET);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VOLUME, 4100);

    set_ac(27);
}
