/*
 *  /d/Sparkle/guilds/new_merc/event/warrior_plate.c
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
    set_name("breastplate");
    add_name( ({ "plate" }) );
    set_adj( ({ "thick", "iron", "breast" }) );

    set_short("thick iron breastplate");
    set_long("There is nothing lovely about the workmanship on this"
      + " plate armour. Nonetheless, it looks like it would do an"
      + " excellent job protecting the wearer from harm.\n");

    set_default_armour(40, A_BODY, ({ -1, 2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(40)+random(50)-25);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(40,A_BODY)+random(100)-50);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
} /* create_armour */
