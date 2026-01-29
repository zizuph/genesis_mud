/*
 * h_kyller.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* This kyller belongs to Van Helsing. */
/* coded by Calonderiel 930906         */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("kyller");
    set_adj("leather");
    add_adj("stout");
    set_short("leather kyller");
    set_long("A stout kyller made of elk leather.\n");

    set_default_armour(8, A_BODY | A_ARMS, ({-1, 1, 0}), 0);

    add_prop(OBJ_I_WEIGHT, 3700);
    add_prop(OBJ_I_VOLUME, 1600);
}
