/*  Shield for trolls in Arnor
 *  Coded by Tigerlily, April 10, 2005
 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

int ac = 40;

void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_adj(({"blackened", "iron"}));
    set_short("blackened iron shield");
    set_long("This shield is made of blackened iron " +
        "delved from the Misty Mountains. It has " +
        "the look of stout dwarven craftsmanship.\n"); 

    set_default_armour(ac, A_SHIELD, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, 4000); 
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
}

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}
