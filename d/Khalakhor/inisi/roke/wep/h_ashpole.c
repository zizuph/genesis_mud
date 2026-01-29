/*
 * h_ashpole.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* This is van Helsing's ashpole 
   coded by Calonderiel 930906   */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    /* Set name, short description and long description */
    set_name("ashpole");
    add_name("pole");
    set_short("sharpened ashpole");
    set_long("A short ashpole, sharpened at one end.\n");

    /* Better add an adjective or two */
    set_adj("sharpened");

    set_default_weapon(3, 2, W_KNIFE, W_IMPALE, W_ANYH, 0);

    add_prop(OBJ_I_VOLUME, 300);
}
