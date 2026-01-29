/*
 * coat.c
 *
 * Used in npc/campguard.c
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
    set_name("coat");
    set_adj(({"thick", "leather"}));
    set_short("thick leather coat");
    set_long("This coat would be nice to wear in the Gontish winter.\n");

    set_ac(10);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 13000);
    add_prop(OBJ_I_VOLUME, 7000);
}
