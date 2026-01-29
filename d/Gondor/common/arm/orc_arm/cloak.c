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
    set_name("cloak");
    add_name("orc-cloak");
    set_pname("cloaks");
    add_pname("orc-cloaks");
    set_adj("black");
    add_adj(({ "filthy", "orc", "smelly" }));
    set_short("filthy black cloak");
    set_pshort("filthy black cloaks");
    set_long(BSN("A smelly orc-cloak. Not of the best quality from the "+
    "beginning, even in worse shape now. It looks as it never has been "+
    "washed."));

    set_default_armour(2, A_ROBE, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(2, A_ROBE)); 
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(2));
}
