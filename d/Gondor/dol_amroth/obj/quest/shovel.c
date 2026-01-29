/* -*- Mode: C -*-
 *
 * obj/quest/shovel.c
 *
 * Skippern 20(c)02
 *
 * A shovel that can be used to dig in the garden
 */
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("shovel");
    set_short("old shovel");
    set_pshort("old shovels");
    set_long("This is an old shovel. It can be used to dig in the ground.\n");
    add_adj("old");

    set_hit(4);
    set_pen(0);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE,  50);
}
