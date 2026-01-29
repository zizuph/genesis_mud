/*
 *  /d/Sparkle/area/orc_temple/arm/priest_robe.c
 *
 *  Robe for the orc priests in the Sparkle Dungeons beneath the orc
 *  temple. 
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
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
    set_name("robe");
    set_adj( ({ "dirty", "brownish", "green", "brownish-green" }) );

    set_short("dirty brownish-green robe");
    set_long("This robe has strange markings along its borders which"
      + " appear to be arcane symbols of some kind. Though rather dirty,"
      + " it appears to be made by skilled hands.\n");

    set_default_armour(10, A_ROBE, ({ -1, 2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10)+random(50)-25);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(10,A_ROBE)+random(100)-50);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
} /* create_armour */