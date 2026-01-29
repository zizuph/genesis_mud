/*
 *  /d/Sparkle/guilds/new_merc/event/warrior_helm.c
 *
 *  High-level armour for the orc raid event to open the Merc Guild.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types;
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour() 
{
    set_name("helm");
    add_name( ({ "helmet" }) );
    set_adj( ({ "iron", "strong" }) );

    set_short("strong iron helm");
    set_long("Though incredibly thick, the iron of this helm has been"
      + " formed such that it does not weight as much as it might"
      + " had it been made by less skilled hands.\n");

    set_default_armour(40, A_HEAD, ({ -1, 2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(40)+random(50)-25);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(40,A_HEAD)+random(100)-50);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
} /* create_armour */
