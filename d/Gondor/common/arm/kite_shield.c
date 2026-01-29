/*  Armour coded by Arren, November 93 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_adj("kite");
    add_adj(({ "black", "orc" }));
    set_short("black kite shield");
    set_long(BSN("A black orc shield, made of a thin metal sheet on a "+
    "wooden frame. It has the normal kite shape.")); 

    set_default_armour(19, A_SHIELD, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, 4000); 
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(19)+random(100)-50);
}

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}
