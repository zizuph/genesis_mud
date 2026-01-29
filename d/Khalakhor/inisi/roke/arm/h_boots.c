/*
 * h_boots.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* These boots belongs to Van Helsing.
   coded by Calonderiel 930906         */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("boots");
    set_adj("leather");
    add_adj("high");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");

    set_long("These high leather boots are of excellent quality,\n" +
             "even though they are well used they look as good as new.\n");

    set_default_armour(8, A_FEET | A_LEGS, ({-1, 1, 0}), 0);

    add_prop(OBJ_I_WEIGHT, 2300);
    add_prop(OBJ_I_VOLUME, 1200);
}
