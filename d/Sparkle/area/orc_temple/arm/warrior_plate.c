/*
 *  /d/Sparkle/area/orc_temple/arm/warrior_plate.c
 *
 *  Armour for the warrior orcs in the Sparkle Temple.
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
    set_name("breastplate");
    add_name( ({ "plate" }) );
    set_adj( ({ "thick", "iron", "breast" }) );

    set_short("thick iron breastplate");
    set_long("There is nothing lovely about the workmanship on this"
      + " plate armour. Nonetheless, it looks like it would do an"
      + " excellent job protecting the wearer from harm.\n");

    set_default_armour(25, A_BODY, ({ -1, 2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(10)-5);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(25,A_BODY)+random(40)-20);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
} /* create_armour */