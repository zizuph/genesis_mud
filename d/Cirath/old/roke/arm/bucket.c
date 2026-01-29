/*
 * bucket.c
 *
 * Used in npc/orc2.c
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
    set_short("wooden bucket");
    set_long("It's an ordinary wooden bucket. It is very leaky and is not " +
             "suitable for carrying anything.\n");
    set_name("bucket");
    add_name("helmet");
    set_adj("wooden");

    set_ac(5);
    set_am(({-1, 1, 0}));

    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
