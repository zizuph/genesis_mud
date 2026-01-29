/*
 *  /d/Sparkle/area/orc_temple/arm/warrior_helm.c
 *
 *  Head armour for the warrior goblins in the Sparkle Temple.
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
      + " formed such that it does not weigh as much as it might"
      + " had it been made by less skilled hands.\n");

    set_default_armour(20, A_HEAD, ({ -1, 2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(20)+random(20)-10);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(20,A_HEAD)+random(30)-15);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
} /* create_armour */
