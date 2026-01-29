/*
 * h_mallet.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* This is van Helsing's mallet */
/* coded by Calonderiel 930906  */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    /* Set name, short description and long description */
    set_name("mallet");
    add_name("club");
    set_short("wooden mallet");
    set_long("This is a small wooden mallet, not much of a weapon, " +
             "but a carpenter might find it useful.\n");

    /* Better add an adjective or two */
    set_adj("wooden");
    add_adj("small");

    set_default_weapon(5, 3, W_CLUB, W_BLUDGEON, W_RIGHT, 0);

    add_prop(OBJ_I_VOLUME, 400);
}
