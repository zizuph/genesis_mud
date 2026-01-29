/*
 *  /d/Sparkle/area/orc_temple/arm/crude_leather.c
 *
 *  Low-level armour for the orc guards in training in the dungeons beneath
 *  the orc temple in Sparkle.
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
    set_name("vest");
    add_name("leather");
    set_adj( ({ "crude", "leather" }) );

    set_short("crude leather vest");
    set_long("The art of leatherwork was surely not well-studied by"
      + " the maker of this armour. Nonetheless, it probably provides"
      + " a certain amount of basic protection.\n");

    set_default_armour(14, A_BODY, ({ -1, 2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(14)+random(50)-25);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(14,A_BODY)+random(100)-50);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
} /* create_armour */
