/* Armour coded by Arren, June 93 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("gambeson");
    set_pname("gambesons");
    set_adj("quilt");
    add_adj(({ "grimy", "dirty", "filthy", "orc" }));
    set_short("grimy gambeson");
    set_long(BSN(
    "This type of armour is usually worn as padding under some "+
    "heavier armour, but it can be used on its own. It's made of quilt. "+
    "The gambeson is very dirty, filth is ingrained in it. You wonder if "+
    "it's flea-infested."));

    set_default_armour(12, A_BODY, ({ -1, -1, 2 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(12, A_BODY));
    add_prop(OBJ_I_VOLUME, 1100); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12)+random(100)-50);
}
