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
    set_adj("round");
    add_adj(({ "red", "wooden", "orc"}));
    set_short("red round shield");
    set_long(BSN("A round wooden shield painted red. Made with an iron "+
    "boss in the center to protect the handle."));

    set_default_armour(14, A_SHIELD, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(14, A_SHIELD));  
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(14)+random(100)-50);
}

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}
