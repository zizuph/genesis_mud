/* -*- Mode: C -*-
 *
 * g_wing.c
 * By Skippern
 * May 2004
 *
 */
inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name( ({ "armour", "wing" }) );
    set_pname( ({ "armours", "wings" }) );
    set_adj("black");
    add_adj("leathery");
    set_short("black leathery wing");
    set_pshort("black leathery wings");
    set_long("This is a black leathery wing, similar in shape with " +
	     "a bat's wing. It seems to be able to protect your body.\n");

    set_default_armour(4,A_ROBE,0,0);
    add_prop(OBJ_I_WEIGHT,5800);
    add_prop(OBJ_I_VOLUME,700);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(14) + random(200) - 200 );
}



