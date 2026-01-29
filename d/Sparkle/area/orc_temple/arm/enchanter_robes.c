/*
 *  /d/Sparkle/area/orc_temple/arm/enchanter_robes.c
 *
 *  These are the robes of Karkadeld, the Enchanter of Sparkle.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
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
    add_name( ({ "robes", "set", }) );
    set_adj( ({ "ornate", "crafted", "ornately", "ornately-crafted",
                "magenta" }) );

    set_short("set of ornately-crafted magenta robes");
    set_pshort("sets of ornately-crafted magenta robes");

    set_long("Exotic stones of varied colors and shapes have been"
      + " sewn into the cowl of these richly woven magenta robes.\n");

    set_default_armour(20, A_ROBE, ({ -1, 2, -1 }), 0);
    set_likely_break(1);
    add_prop( OBJ_I_VALUE,     0 );
    add_prop( OBJ_I_WEIGHT, 1200 );
    add_prop( OBJ_I_VOLUME,  650 );

    set_looseness(20);
    set_layers(1);
} /* create_armour */
