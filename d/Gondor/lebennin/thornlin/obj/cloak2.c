
inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("cloak");
    add_name("robe");
    set_adj("light");
    set_adj("bright-grey");
    set_short("bright-grey cloak");
    set_long(BSN("This is a bright-grey cloak made of light cloth, it "+
	"seems somewhat strong."));
    set_default_armour(3, A_ROBE, (({ 0, 0, 1})), 0);
    add_prop(OBJ_I_WEIGHT, 210);   /* 210 gram */
    add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+random(20));
}
