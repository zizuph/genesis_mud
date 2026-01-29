/*
 * h_cloak.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Van Helsings cloak.
   coded by Calonderiel 930906  */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("cloak");
    set_adj("black");
    add_adj("large");
    set_short("black cloak");
    set_long("A large black cloak, used to keep rain out.\n");

    set_default_armour(5, A_ROBE, ({-1, 1, 0}), 0);

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 2000);
}
