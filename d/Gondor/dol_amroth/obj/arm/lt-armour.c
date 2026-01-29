/* -*- Mode: C -*-
 *
 * lt-armour.c
 * By Skippern
 * June 2000
 *
 */
inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name( ({ "armour" }) );
    set_pname( ({ "armours" }) );
    set_adj("light");
    add_adj("leather");
    set_short("light armour");
    set_pshort("light armours");
    set_long("This is a light leather armour.\n");

    set_default_armour(6,A_BODY,0,0);
    add_prop(OBJ_I_WEIGHT,5800);
    add_prop(OBJ_I_VOLUME,700);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(14) + random(200) - 200 );
}



