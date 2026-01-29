/*
 * coward_shirt.c
 *
 * Used in npc/coward.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
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
    set_name("leathershirt");
    set_short("soft leathershirt");
    set_adj("soft");
    set_long("A scruffy-looking shirt, made out of leather.\n");
    set_ac(5);
    set_am(({1, 1, -2}));                  /* impale,slash,bludgeon */

    set_at(A_TORSO | A_ARMS);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 800);
}
