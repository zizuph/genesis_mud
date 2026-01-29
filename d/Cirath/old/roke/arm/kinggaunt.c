/*
 * kinggaunt.c
 *
 * Used in npc/kingghost.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* plural removed by McCram cause it's not needed and messes things up */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("gauntlets");
    /*
       set_pname("pairs of mithril guantlets");
     */
    set_adj("mithril");
    add_adj("pair of");

    set_short("pair of mithril gauntlets");
    set_long("The gauntlets are made of shining mithril alloy. " +
             "They seem large enough to protect your arms as well " +
             "as your hands.\n");

    set_at(A_HANDS | A_ARMS);
    add_prop(OBJ_I_WEIGHT, 5500);
    add_prop(OBJ_I_VOLUME, 3600);

    set_ac(27);
}
