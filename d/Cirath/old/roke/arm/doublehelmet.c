/*
 * doublehelmet.c
 *
 * Used in npc/sknight2.c npc/campleader.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_short("silver helmet");
    set_long("This helmet is made of very thick silver chains.\n");
    set_name("helmet");
    set_adj("silver");

    set_ac(18);
    set_am(({-1, 1, 0}));

    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VOLUME, 3000);
}
