/*
 * Iron platemail for faerie npcs
 * - Finwe, April 2005
 */
inherit "/std/armour";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{

    set_name("armour");
    add_name("platemail");
    set_short("heavy iron platemail");
    set_adj("heavy");
    set_adj("iron");
    set_long("This is a " + short() + ". It is made from hammered plates " +
        "of iron and to form a shell around you. It looks durable and " +
        "would probably protect you well during battles.\n");
    set_ac(7+random(5));
    set_at(A_TORSO);
    set_am(({0,0,0}));
    
    add_prop(OBJ_I_VALUE, 250);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 3000);
}