/*
 * steelhelmet.c
 *
 * Used in npc/towerg3.c npc/towerg4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* glindor -93 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_short("steel helmet");
    set_long("This helmet is made of very thick steel.\n");
    set_name("helmet");
    set_adj("steel");

    set_ac(30);
    set_am(({-1, 1, 0}));

    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2500);
}
