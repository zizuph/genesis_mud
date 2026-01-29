/*  Armour coded by Arren, January 94 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("leggings");
    add_name(({ "pair of leggings" }));
    set_pname("leggingses");
    set_adj("grey");
    add_adj("orc");
    set_short("pair of grey leggings");
    set_pshort("pairs of grey leggings");
    set_long(BSN("A pair of grey leggings made of iron strips riveted to "+
    "a hard leather backing."));

    set_default_armour(20, A_LEGS, ({ 1, 1, -2 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));
    add_prop(OBJ_I_VOLUME, 2000); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(100)-50);
}
