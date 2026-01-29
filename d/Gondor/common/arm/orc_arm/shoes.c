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
    set_name("pair of shoes");
    add_name("shoes");
    set_pname("pairs");
    add_pname("shoeses");
    set_adj("iron");
    add_adj(({ "iron-shod", "orc" }));
    set_short("pair of iron-shod shoes");
    set_pshort("pairs of iron-shod shoes");
    set_long(BSN("The normal uncomfortable orc footwear. Hard and mean "+
    "to your feet, but good to trample flowers with."));

    set_default_armour(8, A_FEET, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 400); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(50)-25);
}
