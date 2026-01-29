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
    set_name("helmet");
    set_pname("helmets");
    add_name(({ "orc-helmet", "helm", "orc-helm" }));
    set_adj("sturdy");
    add_adj("orc");
    set_short("sturdy orc-helmet");
    set_long(BSN(
    "A sturdy orc-helmet of good quality. It is made of sheet metal."));

    set_default_armour(20, A_HEAD, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_HEAD));
    add_prop(OBJ_I_VOLUME, 900); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(100)-50);
}
